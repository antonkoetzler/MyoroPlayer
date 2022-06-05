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
      case 83: toggleSidebar()
      // Alt + C ~ Toggle controls
      case 67: toggleControls()
    }
  }
})
window.addEventListener("click", () => {
  document.getElementById("errorMessage").style.display = "none"

  // If a taskbar button (not dropdown button) is not clicked, clean dropdowns
  if (event.target.className != "taskbarButton") cleanDropdowns()
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

function toggleControls()
{
  let songlist = document.getElementById("songlist")
  let controls = document.getElementById("controls")
  if (window.getComputedStyle(controls).display == "none") {
    songlist.style.width = "calc(100% - 52px)"
    controls.style.display = "block"
  } else {
    songlist.style.width = "100%"
    controls.style.display = "none"
  }
}
