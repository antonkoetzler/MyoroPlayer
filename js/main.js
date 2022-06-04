const { app, BrowserWindow, ipcMain } = require('electron')

ipcMain.on("msg", (event, data) => { console.log("data") })

// Creates a new window
const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    minWidth: 400,
    minHeight: 400,
    title: "MyoroPlayer",
    webPreferences: {
      nodeIntegration: true
    }
  })
  win.loadFile("index.html")
  win.setMenu(null)
}

// Once app fires a ready event, we may load index.html
app.whenReady().then(createWindow)
