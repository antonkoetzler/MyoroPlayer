Neutralino.init()
Neutralino.events.on("windowClose", exit)

window.addEventListener("keydown", function()
{
  if (event.ctrlKey)
  {
    switch (event.keyCode)
    {
      // Exit program
      case 81: exit()
    }
  }
})
window.addEventListener("click", function()
{
  // Clean .taskbarButton objects if mouse is clicked elsewhere
  if (event.target.className != "taskbarButton") clean()
})

function exit() { Neutralino.app.exit() }

// Disables: taskbar dropdowns
function clean()
{
  // Taskbar objects
  document.getElementById("file").style.display = "none"
  document.getElementById("view").style.display = "none"
  // Directory popup
  document.getElementById("directoryPopup").style.display = "none"
}

// Either enables or disables a dropdown from the taskbar
function toggleDropdown(id)
{
  let dropdown = document.getElementById(id)
  let dropdownDisplay = window.getComputedStyle(dropdown).display
  clean()
  if (dropdownDisplay == "none") dropdown.style.display = "flex"
  else                           dropdown.style.display = "none"
}

// Enables #directoryPopup to add a new playlist
function toggleDirectoryPopup()
{
  document.getElementById("directoryPopup").style.display = "flex"
}
