const { contextBridge, ipcRenderer } = require("electron")

ipcRenderer.on("getPlaylist", (event, dir) => {
  // Turning the dir into a string
  let directory = new String(dir)

  // Getting the name of the directory
  let name = null
  if (directory == "/") name = directory
  else
  {
    for (var i = (directory.length - 1); i >= 0; i--)
    {
      if (directory[i] == '/')
      {
        name = directory.substr(i + 1)
        break
      }
    }
  }

  // Making sure the name isn't too long
  if (name.length > 12) name = name.substr(0, 12)

  // Adding button to #sidebar
  let button = document.createElement("button")
  button.innerHTML = name
  button.className = "taskbarButton sidebarButton"
  button.setAttribute("onClick", "openPlaylist('" + directory + "')")
  document.getElementById("sidebar").appendChild(button)

  // Disabling taskbar menus
  document.getElementById("file").style.display = "none"
  document.getElementById("view").style.display = "none"
})

// Creating an ipc API, can use ipc.send(_, _) in index.js now
contextBridge.exposeInMainWorld("ipc", {
  send: (evt, message) => { ipcRenderer.send(evt, message) }
})
