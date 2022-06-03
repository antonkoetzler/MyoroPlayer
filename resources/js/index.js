Neutralino.init()
Neutralino.events.on("windowClose", exit)

window.addEventListener("keydown", function()
{
  if (event.ctrlKey)
  {
    switch (event.keyCode)
    {
      // Exit program
      case 81: exit()
      // Add playlist
      case 78: toggleDirectoryPopup()
    }
  }
  if (event.altKey)
  {
    switch (event.keyCode)
    {
      // Toggle playlist sidebar
      case 83: toggleSidebar()
    }
  }
})
window.addEventListener("click", function()
{
  // Clean .taskbarButton objects if mouse is clicked elsewhere
  let className = event.target.className
  if (className != "taskbarButton" && className != "taskbarButton sidebarButton") clean()
})

// Loading playlists to the sidebar on a program launch or reload
window.onload = async function()
{
  let savedPlaylists = await Neutralino.filesystem.readFile(".savedPlaylists")
  // Seperating directories and playlist names in .savedPlaylists in an array
  let directories = []
  let names = []
  let temp = ""
  while (true)
  {
    for (var i = 0; i < savedPlaylists.length; i++)
    {
      if (savedPlaylists[i] == '\n')
      {
        let temp = ""
        if (NL_OS == "Windows") temp = savedPlaylists.substr(0, i - 1)
        else                    temp = savedPlaylists.substr(0, i)
        for (var o = (temp.length - 2); o >= 0; o--)
        {
          if (temp[o] == '/')
          {
            names.push(temp.substr(o + 1))
            names[names.length - 1] = names[names.length - 1].substr(0, names[names.length - 1].length - 1)
            break
          }
        }
        directories.push(temp)
        savedPlaylists = savedPlaylists.substr(i + 1)
        break
      }
    } if (savedPlaylists.length == 0) break
  }

  // Adding to #sidebar
  let button = ""
  let sidebar = document.getElementById("sidebar")
  for (var i = 0; i < names.length; i++)
  {
    button = "<button class=\"taskbarButton sidebarButton\" onclick=\"openPlaylist('" + directories[i].replaceAll('\'', '\\' + '\'') + "')\">" + names[i] + "</button>"
    sidebar.innerHTML += button
  }
}

function exit() { Neutralino.app.exit() }

// Disables: taskbar dropdowns
function clean()
{
  // Taskbar objects
  document.getElementById("file").style.display = "none"
  document.getElementById("view").style.display = "none"
}

// Either enables or disables a dropdown from the taskbar
function toggleDropdown(id)
{
  let dropdown = document.getElementById(id)
  let dropdownDisplay = window.getComputedStyle(dropdown).display
  clean()
  document.getElementById("directoryPopup").style.display = "none"
  if (dropdownDisplay == "none") dropdown.style.display = "flex"
  else                           dropdown.style.display = "none"
}

// Toggles the playlist sidebar
function toggleSidebar()
{
  clean()
  let sidebar = document.getElementById("sidebar")
  if (window.getComputedStyle(sidebar).display == "none")
  {
    sidebar.style.display = "flex"
    document.getElementById("songlist").style.width = "calc(100% - 152px)"
  }
  else
  {
    sidebar.style.display = "none"
    document.getElementById("songlist").style.width = "100%"
  }
}

// Enables #directoryPopup to add a new playlist
function toggleDirectoryPopup()
{
  let directoryPopup = document.getElementById("directoryPopup")
  let directoryPopupDisplay = window.getComputedStyle(directoryPopup).display
  document.getElementById("directoryPopupErrorMessage").style.display = "none"

  clean()

  if (directoryPopupDisplay == "none")
  {
    directoryPopup.style.display = "flex"
    document.getElementById("directoryPopupInput").focus()
  } else directoryPopup.style.display = "none"
}

// Adds a playlist to #sidebar and .savedPlaylists
async function addPlaylist()
{
  // Grabbing the directory
  let directory = document.getElementById("directoryPopupInput").value

  // Switching all backslashes with forward slashes     (makes life easier)
  directory = directory.replace(/\\/g, '/')

  // Checking if it's a valid directory
  try
  {
    let files = await Neutralino.filesystem.readDirectory(directory)

    // Checking for a relative path (and converting it to a full directory)
    if (directory[0] != '/' && directory[1] != ":")
    {
      // Seperating the relative directory into steps to get the full directory
      let steps = []
      while (true)
      {
        for (var i = 0; i < directory.length; i++)
        {
          if (directory[i] == '/' || i == (directory.length - 1))
          {
            steps.push(directory.substr(0, i + 1))
            directory = directory.substr(i + 1)
            break
          }
        } if (directory.length == 0) break
      }

      // Setting directory as MyoroPlayer's root directory
      // We then apply the steps array to get the full directory
      directory = NL_CWD
      for (var i = 0; i < steps.length; i++)
      {
        if (steps[i] == "../")
        {
          for (var o = (directory.length - 1); o >= 0; o--)
          {
            if (directory[o] == '/')
            {
              directory = directory.substr(0, o)
              break
            }
          }
        }
        // A directory name
        if (steps[i] != "./" && steps[i] != "../")
        {
          directory += "/" + steps[i]
          if (directory[directory.length - 1] == '/') directory = directory.substr(0, directory.length - 1)
        }
      }
    }

    // Checking for duplicate playlists that have been added
    let savedPlaylists = await Neutralino.filesystem.readFile(".savedPlaylists")
    // Placing directories in .savedPlaylists into an array
    let playlists = []
    while (true)
    {
      for (var i = 0; i < savedPlaylists.length; i++)
      {
        if (savedPlaylists[i] == '\n')
        {
          playlists.push(savedPlaylists.substr(0, i - 1))
          savedPlaylists = savedPlaylists.substr(i + 1)
          break
        }
      } if (savedPlaylists.length == 0) break
    }
    // Placing a slash at the end as .savedPlaylists' directories do this
    // Also, this makes life easier
    if (directory[directory.length - 1] != '/') directory += '/'
    // Checking for duplicates
    if (playlists.includes(directory))
    {
      let errorMessage = document.getElementById("directoryPopupErrorMessage")
      errorMessage.innerHTML = "Duplicate directory added"
      errorMessage.style.display = "block"
      return
    }

    // Adding directory to .savedPlaylists
    let string = directory + '\n'
    await Neutralino.filesystem.appendFile(".savedPlaylists", string)

    // Grabbing the playlist name without the directory to display on #sidebar
    let playlistName = ""
    for (var i = (directory.length - 2); i >= 0; i--)
    {
      if (directory[i] == '/')
      {
        playlistName = directory.substr(i + 1)
        playlistName = playlistName.substr(0, playlistName.length - 1)
        break
      }
    }

    // Finally, adding the playlist to #sidebar
    let button = "<button class=\"taskbarButton sidebarButton\" onclick=\"openPlaylist('" + directory.replaceAll('\'', '\\' + '\'') + "')\">" + playlistName + "</button>"
    document.getElementById("sidebar").innerHTML += button

    document.getElementById("directoryPopup").style.display = "none"
  }
  catch (error)
  {
    let errorMessage = document.getElementById("directoryPopupErrorMessage")
    errorMessage.innerHTML = "Invalid directory"
    errorMessage.style.display = "block"
  }
}
// Calls addPlaylist() when enter is pressed
function addPlaylistEnterActivation() { if (event.key == "Enter") addPlaylist() }

// Opens a playlist's directory and lists the songs on the screen
async function openPlaylist(directory)
{
  let files = await Neutralino.filesystem.readDirectory(directory)

  // Adding only mp3 files, and storing names and directories of songs in arrays
  let names = []
  let directories = []
  // Temp variables
  let file = ""
  let name = ""
  let extension = ""
  for (var i = 0; i < files.length; i++)
  {
    if (files[i].entry != "." && files[i].entry != "..")
    {
      file = files[i].entry

      // Making sure it's an mp3 (grabs extension and name of song without extension)
      for (var o = (file.length - 1); o >= 0; o--)
      {
        if (file[o] == '.')
        {
          extension = file.substr(o + 1)
          name = file.substr(0, o)
          break
        }
      }

      if (extension == "mp3")
      {
        file = directory + file
        directories.push(file)
        names.push(name)
      }
    }
  }

  // Adding to the songlist
  let songlist = document.getElementById("songlist")
  songlist.innerHTML = ""
  let button = ""
  for (var i = 0; i < names.length; i++)
  {
    button = "<button ondblclick=\"playSong('" + directories[i].replaceAll('\'', '\\' + '\'') + "')\">" + names[i] + "</button>"
    songlist.innerHTML += button
  }
}

// Plays a song
async function playSong(directory)
{
  // Turning the MP3 into a blob file to load into #player
  var data = await Neutralino.filesystem.readBinaryFile(directory)
  var blob = new Blob([new Uint8Array(data)], {type: "audio/mpeg"})
  var blobUrl = URL.createObjectURL(blob)
  let player = document.getElementById("player")
  player.src = blobUrl
  player.play()
}
