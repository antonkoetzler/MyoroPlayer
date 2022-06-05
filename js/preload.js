const { contextBridge, ipcRenderer } = require("electron")
const os = require("os")

// Where previously added playlists are added on program start
window.onload = () => {
  alert("Loaded")
}

// Adds the directory selected in ipcMain.on("addPlaylist...
ipcRenderer.on("getPlaylist", (event, dir) => {
  // Turning the dir into a string
  let directory = new String(dir)

  // Getting the name of the directory
  let name = null
  if (directory == "/" || directory.length == 3 && directory.substr(1) == ":\\")
    name = directory
  else
  {
    for (var i = (directory.length - 1); i >= 0; i--)
    {
      if (directory[i] == '/' || directory[i] == '\\')
      {
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
  directory = directory.replaceAll('\\', "\\\\")

  // Adding button to #sidebar
  let button = document.createElement("button")
  button.innerHTML = name
  button.className = "taskbarButton sidebarButton"
  button.setAttribute("onClick", "openPlaylist('" + directory +  "')")
  document.getElementById("sidebar").appendChild(button)

  // Since we don't have access to cleanDropdowns, we disable dropdowns manually
  document.getElementById("file").style.display = "none"
  document.getElementById("view").style.display = "none"
})

// Creating an ipc API, can use ipc.send(_, _) in index.js now
contextBridge.exposeInMainWorld("ipc", {
  send: (evt, message) => { ipcRenderer.send(evt, message) }
})
