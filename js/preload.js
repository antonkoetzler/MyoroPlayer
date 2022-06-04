const { contextBridge, ipcRenderer } = require("electron")

// Creating an ipc API, can use ipc.send(_, _) in index.js now
contextBridge.exposeInMainWorld("ipc", {
  send: (evt, message) => { ipcRenderer.send(evt, message) }
})
