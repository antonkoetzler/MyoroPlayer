const { contextBridge, ipcRenderer } = require("electron")
const os = require("os") // For getting OS
const fs = require("fs") // For reading files (.savedPlaylists)
const path = require("path")

// Where previously added playlists are added on program start
window.onload = () => {
  fs.readFile(path.join(__dirname, "../.savedPlaylists"), { encoding: "utf-8" }, (error, data) => {
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
            button.setAttribute("onClick", "openPlaylist('" + JSON.stringify(directory) + "')")
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
  fs.readFile(path.join(__dirname, "../.savedPlaylists"), { encoding: "utf-8" }, (error, data) => {
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
        button.setAttribute("onClick", "openPlaylist('" + JSON.stringify(directory) + "')")
        document.getElementById("sidebar").appendChild(button)

        // Adding directory to .savedPlaylists
        fs.appendFile(path.join(__dirname, "../.savedPlaylists"), directory + '\n', (err) => { if (err) console.log(err) })

        document.getElementById("file").style.display = "none"
        document.getElementById("view").style.display = "none"
        document.getElementById("errorMessage").style.display = "none"
      }
    }
    else console.log(error)
  })
})

// Creating an ipc API, can use ipc.send(_, _) in index.js now
contextBridge.exposeInMainWorld("ipc", {
  send: (evt, message) => { ipcRenderer.send(evt, message) }
})
