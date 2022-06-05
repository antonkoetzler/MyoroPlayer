window.addEventListener("keydown", () => {
  if (event.ctrlKey)
  {
    switch (event.keyCode)
    {
      // Ctrl + Q ~ Quit
      case 81: quit()
      // Ctrl + N ~ Add playlist
      case 78: addPlaylist()
    }
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

function addPlaylist() { ipc.send("addPlaylist", "") }

function openPlaylist(directory) { alert(directory) }
