const { app, BrowserWindow, ipcMain, dialog } = require("electron")
const path = require("path")

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

  // Add a playlist
  ipcMain.on("addPlaylist", (event, data) => {
    // Opens a native dialog to add a directory
    dialog.showOpenDialog(win, { properties: ["openDirectory"] }).then(result => {
      // After the user uses the window, we send the directory to the renderer
      if (!result.canceled) event.reply("getPlaylist", result.filePaths)
    }).catch(err => {
      console.log(err)
    })
  })

  // Open a playlist
  ipcMain.on("openPlaylist", (event, directory) => {
    event.reply("getPlaylistDirectory", directory)
  })

  // Quit event
  ipcMain.on("quit", (event, data) => { app.exit(0) })
}

// Once app fires a ready event, we may load index.html
app.whenReady().then(createWindow)
