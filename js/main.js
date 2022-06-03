const { app, BrowserWindow } = require('electron')

// Creates a new window
const createWindow = () =>
{
  const win = new BrowserWindow({
    width: 800,
    height: 600
  })
  win.loadFile("index.html")
  win.setMenu(null)
}

// Once app fires a ready event, we may load index.html
app.whenReady().then(() => { createWindow() })
