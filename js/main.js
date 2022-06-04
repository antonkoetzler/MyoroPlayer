const { app, BrowserWindow, ipcMain } = require("electron")
const path = require("path")

// Quit event
ipcMain.on("quit", (event, data) => { app.exit(0) })

// Creates a new window
const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    minWidth: 400,
    minHeight: 400,
    title: "MyoroPlayer",
    webPreferences: {
      preload: path.join(__dirname, "preload.js")
    }
  })
  win.loadFile("index.html")
  win.setMenu(null)
}

// Once app fires a ready event, we may load index.html
app.whenReady().then(createWindow)
