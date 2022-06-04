const { app, BrowserWindow, globalShortcut } = require('electron')

// Creates a new window
const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    minWidth: 400,
    minHeight: 400
  })
  win.loadFile("index.html")
  win.setMenu(null)
}

// Once app fires a ready event, we may load index.html
app.whenReady().then(createWindow)
app.whenReady().then(() => {
  // Setting Ctrl + Q to quit the application
  globalShortcut.register("Ctrl+Q", () => { app.exit(0) })
}).then(createWindow)
