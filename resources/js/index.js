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

function exit() { Neutralino.app.exit() }
