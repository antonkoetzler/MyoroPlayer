const { app, BrowserWindow, ipcMain, dialog } = require("electron")
const path = require("path")

// Creates a new window
const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    minWidth: 800,
    minHeight: 600,
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

  // Get directory to add converted youtube video
  ipcMain.on("getDirectory", (event, link) => {
    dialog.showOpenDialog(win, { properties: ["openDirectory"] }).then(result => {
      if (!result.canceled) {
        let returnArray = [link, result.filePaths[0]] // Returning array of the link and directory
        // Sending to preload.js to run yt2mp3
        event.reply("convertLink", returnArray)
      }
    }).catch(err => { console.log(err) })
  })

  // Quit event
  ipcMain.on("quit", (event, data) => { app.exit(0) })
}

// Once app fires a ready event, we may load index.html
app.whenReady().then(createWindow)
