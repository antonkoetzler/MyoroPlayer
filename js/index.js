var songCache = [] // Saves previously played songs

// Key combination control
window.addEventListener("keydown", () => {
  document.getElementById("errorMessage").style.display = "none"

  if (event.ctrlKey) {
    switch (event.keyCode) {
      // Ctrl + Q ~ Quit
      case 81: quit()
      // Ctrl + N ~ Add playlist
      case 78: addPlaylist()
    }
  }
  if (event.altKey) {
    switch (event.keyCode) {
      // Alt + S ~ Toggle sidebar
      case 83:
        toggleSidebar()
        break
      // Alt + C ~ Toggle controls
      case 67:
        toggleControls()
        break
    }
  }
})
// Click control
window.addEventListener("click", () => {
  document.getElementById("errorMessage").style.display = "none"
  document.getElementById("contextMenu").style.display = "none"

  // If a taskbar button (not dropdown button) is not clicked, clean dropdowns
  if (event.target.className != "taskbarButton") cleanDropdowns()
})
// Context menu (right click menu)
window.addEventListener("contextmenu", () => {
  if (event.target.className == "taskbarButton songButton")
  {
    let contextMenu = document.getElementById("contextMenu")

    // We normalize the position of the context menu to not be messed up
    // Positions of where the context menu will be placed
    let posX = window.innerWidth
    let posY = window.innerHeight
    let mousePosX = event.clientX
    let mousePosY = event.clientY

    if ((posX - mousePosX) < 165) mousePosX = posX - 165
    if ((posY - mousePosY) < 65)  mousePosY = posY - 65

    contextMenu.style.left = mousePosX + "px"
    contextMenu.style.top = mousePosY + "px"
    contextMenu.style.display = "flex"
  }
})

// Disables every dropdown menu enabled
function cleanDropdowns() {
  document.getElementById("file").style.display = "none"
  document.getElementById("view").style.display = "none"
}

// Enables/disables a dropdown menu
function toggleDropdown(id) {
  let dropdown = document.getElementById(id)
  let dropdownDisplay = window.getComputedStyle(dropdown).display
  cleanDropdowns()
  if (dropdownDisplay == "none") dropdown.style.display = "flex"
  else                           dropdown.style.display = "none"
}

function quit() { ipc.send("quit", "") }

// Adds a new playlist and caches it so it'll automatically load in next time
function addPlaylist() { ipc.send("addPlaylist", "") }

// Opens a playlist and lists them in the song view
function openPlaylist(directory) { ipc.send("openPlaylist", directory) }

function toggleSidebar()
{
  let sidebar = document.getElementById("sidebar")
  let main = document.getElementById("main")
  if (window.getComputedStyle(sidebar).display == "none") {
    main.style.width = "calc(100% - 124px)"
    sidebar.style.display = "block"
  } else {
    main.style.width = "100%"
    sidebar.style.display = "none"
  }
}

function toggleControls() {
  let songlist = document.getElementById("songlist")
  let controls = document.getElementById("controls")
  if (window.getComputedStyle(controls).display == "none") {
    songlist.style.height = "calc(100% - 77px)"
    controls.style.display = "block"
  } else {
    songlist.style.height = "100%"
    controls.style.display = "none"
  }
}

function playSong(directory)
{
  let controls = document.getElementById("controls")
  if (window.getComputedStyle(controls).display == "none")
  {
    document.getElementById("songlist").style.height = "calc(100% - 77px)"
    controls.style.display = "block"
  }

  // Loading the song to the music player
  let player = document.getElementById("player")
  player.src = directory
  player.play()

  // Adding the directory of the song to songCache (global array)
  songCache.push(directory)
}

// Changes the src and background of a song control button (play, prev, etc)
function songControlButtonHover(id) {
  let button = document.getElementById(id)
  switch (id)
  {
    case "shuffle":
      button.src = "img/shuffleHover.png"
      break
    case "previous":
      button.src = "img/previousHover.png"
      break
    case "play":
      button.src = "img/playHover.png"
      break
    case "next":
      button.src = "img/nextHover.png"
      break
  }
  button.style.background = "#7393B3"
}

// Resets changes made by songControlButtonHover(id)
function songControlButtonNotHovered(id) {
 let button = document.getElementById(id)
 switch (id)
 {
   case "shuffle":
     button.src = "img/shuffle.png"
     break
   case "previous":
     button.src = "img/previous.png"
     break
   case "play":
     button.src = "img/play.png"
     break
   case "next":
     button.src = "img/next.png"
     break
  }
  button.style.background = "none"
}

// Function for the play button
function togglePlay() {
  let player = document.getElementById("player")
  if (player.paused) player.play()
  else               player.pause()
}
