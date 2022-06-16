const { contextBridge, ipcRenderer } = require("electron")
const os = require("os")              // For getting OS
const fs = require("fs")              // For reading files (.savedPlaylists)
const path = require("path")
const { exec, execFile, execFileSync } = require("child_process") // For executing yt2mp3 script

// Creating an ipc API, can use ipc.send(_, _) in index.js now
contextBridge.exposeInMainWorld("ipc", {
  send: (evt, message) => { ipcRenderer.send(evt, message) }
})
// Create an fs API, can use readdir in index.js
contextBridge.exposeInMainWorld("fs", {
  // Returns a directory's files
  readDirectory: (directory) => { return fs.readdirSync(directory, { encoding: "utf-8" }) }
})

// Where previously added playlists are added on program start
window.onload = () => {
  fs.readFile(".savedPlaylists", { encoding: "utf-8" }, (error, data) => {
    if (!error) {
      while (true)
      {
        if (data.length == 0) break
        for (var i = 0; i < data.length; i++)
        {
          if (data[i] == '\n')
          {
            let directory = data.substr(0, i)
            data = data.substr(i + 1)

            let name = null
            let split = null
            if (directory == "/" || directory.length == 3 && directory.substr(1) == ":\\")
              name = directory
            else {
              if (os.platform() == "win32") split = directory.split("\\")
              else                          split = directory.split('/')
              name = split[split.length - 2]
            }

            let button = document.createElement("button")
            button.innerHTML = name
            button.className = "taskbarButton sidebarButton"
            button.setAttribute("onClick", "openPlaylist(" + JSON.stringify(directory) + ")")
            document.getElementById("sidebar").appendChild(button)

            break
          }
        }
      }
    }
  })
}

// Adds the directory selected in ipcMain.on("addPlaylist...
ipcRenderer.on("getPlaylist", (event, dir) => {
  // Turning the dir into a string
  let directory = new String(dir)

  // Getting the name of the directory
  let name = null
  if (directory == "/" || directory.length == 3 && directory.substr(1) == ":\\")
    name = directory
  else {
    for (var i = (directory.length - 1); i >= 0; i--) {
      if (directory[i] == '/' || directory[i] == '\\') {
        name = directory.substr(i + 1)
        break
      }
    }
  }

  // Making sure the name isn't too long
  if (name.length > 12) name = name.substr(0, 12)

  // Adding a slash at the end of the directory and making it JS passable
  if (os.platform() == "win32" && directory.length != 3 && directory.substr(1) !== ":\\") directory += '\\'
  else if (os.platform() == "linux" && directory != "/")                                  directory += '/'
  // directory = directory.replaceAll('\\', "\\\\") // Works appropriately when passed via JS argument

  // Reads .savedPlaylists and looks for duplicate directories
  fs.readFile(".savedPlaylists", { encoding: "utf-8" }, (error, data) => {
    if (!error) {
      data = data.toString()

      // Checks for duplicates
      if (data.includes(directory)) {
        let errorMessage = document.getElementById("errorMessage")
        errorMessage.innerHTML = "Duplicate Playlist/Directory Added"
        errorMessage.style.display = "block"
      } else {
        // Adding button to #sidebar
        let button = document.createElement("button")
        button.innerHTML = name
        button.className = "taskbarButton sidebarButton"
        button.setAttribute("onClick", "openPlaylist(" + JSON.stringify(directory) + ")")
        document.getElementById("sidebar").appendChild(button)

        // Adding directory to .savedPlaylists
        fs.appendFile(".savedPlaylists", directory + '\n', (err) => { if (err) console.log(err) })

        document.getElementById("file").style.display = "none"
        document.getElementById("view").style.display = "none"
        document.getElementById("errorMessage").style.display = "none"
      }
    }
    else console.log(error)
  })
})

// Opens a playlist
ipcRenderer.on("getPlaylistDirectory", (event, dir) => {
  document.getElementById("songlist").innerHTML = ""

  // Highlighting the selected playlist
  // Getting the name of the playlist
  let playlistName = null
  if (dir == 'C:\\' || dir == '/') playlistName = dir
  else {
    for (var i = (dir.length - 2); i >= 0; i--) {
      if (dir[i] == '/' || dir[i] == '\\') {
        playlistName = dir.substr(i + 1)
        playlistName = playlistName.substr(0, playlistName.length - 1)
        break
      }
    }
  }
  let playlists = document.getElementsByClassName("taskbarButton sidebarButton")
  for (var i = 0; i < playlists.length; i++) {
    if (playlists[i].innerHTML == playlistName) {
      playlists[i].style.background = "#7393B3"
      playlists[i].style.color = "#FFFFFF"
    } else {
      playlists[i].style.background = "none"
      playlists[i].style.color = "#7393B3"
    }
  }

  fs.readdir(dir, { encoding: "utf-8" }, (error, files) => {
    if (!error)
    {
      files.forEach((file) => {
        // Getting name and extension
        let name = ""
        let extension = ""
        for (var i = (file.length - 1); i >= 0; i--)
        {
          if (file[i] == '.')
          {
            name = file.substr(0, i)
            extension = file.substr(i + 1)
            break
          }
        }

        if (extension == "mp3")
        {
          let songDirectory = dir + file
          let button = document.createElement("button")
          button.innerHTML = name
          button.className = "taskbarButton songButton"
          button.name = songDirectory
          button.setAttribute("onDblClick", "playSong(" + JSON.stringify(songDirectory) + ")")
          document.getElementById("songlist").appendChild(button)
        }
      })
    } else console.log(error)
  })
})

// Converts a youtube link to the desired directory
ipcRenderer.on("convertLink", (event, array) => {
  let executable = null
  if (os.platform() == "win32") executable = path.join(__dirname, "../scripts/yt2mp3windows")
  else                          executable = path.join(__dirname, "../scripts/yt2mp3linux")
  execFile(executable, [array[0], array[1]], (error, stdout, stderr) => {
    if (error)       alert(error)
    else if (stderr) alert(stderr)
    else             alert("Conversion complete! Please reload " + array[1] + " to see new song")
  })
})

const jsmediatags = require("jsmediatags")
// Grabs album cover of directory and replaces of #albumCover
ipcRenderer.on("runAlbumCoverScript", (event, directory) => {
  // Grabbing the album cover (if there is one)
  jsmediatags.read(directory, {
    onSuccess: function(tag) {
      let albumCover = tag.tags.picture
      if (albumCover != undefined) {
        var base64String = ""
        for (var i = 0; i < albumCover.data.length; i++)
          base64String += String.fromCharCode(albumCover.data[i])
        var imageUri = "data: " + albumCover.format + ";base64," + window.btoa(base64String)
        document.getElementById("albumCover").src = imageUri
      } else document.getElementById("albumCover").src = path.join(__dirname, "../img/defaultAlbumCover.png")
    }, 
    onError: function(error) {
      alert(error);
    }
  });
})
