var songCache = []                          // Saves previously played songs
var queue = []                              // Saves queued songs
var contextMenuSong = null                  // Song that is right clicked to activate the context menu
var shuffle = 0                             // Global variable to control shuffling songs
var audio = document.createElement("audio") // Our audio player
audio.volume = 0.5
audio.onended = () => { nextSong() }
audio.ontimeupdate = () => {
  let songSlider = document.getElementById("songSlider")
  songSlider.setAttribute("max", audio.duration)
  songSlider.value = audio.currentTime
}

// Key combination control
window.addEventListener("keydown", () => {
  document.getElementById("errorMessage").style.display = "none"

  if (event.ctrlKey) {
    switch (event.keyCode) {
      // Ctrl + Q ~ Quit
      case 81:
        quit()
        break
      // Ctrl + N ~ Add playlist
      case 78:
        addPlaylist()
        break
      case 89:
        youtubeToMP3()
        break
      // Ctrl + Right Arrow Key ~ Next Song
      case 190:
        nextSong()
        break
      // Ctrl + Left Array Key ~ Previous Song
      case 188:
        previousSong()
        break
      // Ctrl + % ~ Shuffle
      case 53:
        toggleShuffle()
        break
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

  if (event.key == "Escape") document.getElementById("youtubeToMP3").style.display = "none"
  if (event.keyCode == 32) togglePlay() // Spacebar to pause/play
})
// Click control
window.addEventListener("click", () => {
  document.getElementById("errorMessage").style.display = "none"
  document.getElementById("contextMenu").style.display = "none"

  // If a taskbar button (not dropdown button) is not clicked, clean dropdowns
  if (event.target.className != "taskbarButton") cleanDropdowns()
 
  if (event.target.id != "youtubeToMP3Input" && event.target.id != "youtubeToMP3Button")
    document.getElementById("youtubeToMP3").style.display = "none"
})
// Context menu (right click menu)
window.addEventListener("contextmenu", () => {
  if (event.target.className == "taskbarButton songButton")
  {
    let contextMenu = document.getElementById("contextMenu")
    contextMenuSong = event.target.name // Save the song that was right clicked

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
  document.getElementById("songControls").style.display = "none"
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

// Fixes characters of song file (not directory) to not mess up our audio player
function fixCharacters(string) {
  for (var i = (string.length - 1); i >= 0; i--)
    if (string[i] == '/' || string[i] == '\\')
      return string.substr(0, i + 1) + encodeURIComponent(string.substr(i + 1))
}

// Changes background and font color of currently playing song
function highlightCurrentSong(directory) {
  directory = decodeURIComponent(directory)
  let songs = document.getElementsByClassName("taskbarButton songButton")
  for (var i = 0; i < songs.length; i++) {
    if (songs[i].name == directory) {
      songs[i].style.background = "#7393B3"
      songs[i].style.color = "#FFFFFF"
    } else {
      songs[i].style.background = "none"
      songs[i].style.color = "#7393B3"
    }
  }
}

// Sets #songName when playing a new song
function setSongName(directory) {
  // Grabbing the name of the song to display
  let songName = null
  for (var i = (directory.length - 1); i >= 0; i--) {
    if (directory[i] == '/' || directory[i] == '\\') {
      songName = directory.substr(i + 1)
      break
    }
  }
  for (var i = (songName.length - 1); i >= 0; i--) {
    if (songName[i] == '.') {
      songName = songName.substr(0, i)
      break
    }
  }
  document.getElementById("songName").innerHTML = songName
}

function playSong(directory)
{
  ipc.send("getAlbumCover", directory)
  setSongName(directory)
  highlightCurrentSong(directory)
  directory = fixCharacters(directory)

  let controls = document.getElementById("controls")
  if (window.getComputedStyle(controls).display == "none")
  {
    document.getElementById("songlist").style.height = "calc(100% - 77px)"
    controls.style.display = "block"
  }

  // Loading the song to the music player
  audio.src = directory
  audio.play()

  // Adding the directory of the song to songCache (global array)
  if (directory != songCache[songCache.length - 1]) songCache.push(directory)
}

// Changes the src and background of a song control button (play, prev, etc)
function songControlButtonHover(id) {
  let button = document.getElementById(id)
  switch (id) {
    case "shuffle":
      if (shuffle == 0) {
        button.src = "img/shuffleHover.png"
        button.style.background = "#7393B3"
      }
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
  if (id != "shuffle") button.style.background = "#7393B3"
}

// Resets changes made by songControlButtonHover(id)
function songControlButtonNotHovered(id) {
  let button = document.getElementById(id)
  switch (id) {
    case "shuffle":
      if (shuffle == 0) {
        button.src = "img/shuffle.png"
        button.style.background = "none"
      }
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
  if (id != "shuffle") button.style.background = "none"
}

// Function for the play button
function togglePlay() {
  if (audio.paused) audio.play()
  else              audio.pause()
}

// Adds a song to the queue array
function queueSong() { queue.push(fixCharacters(contextMenuSong)) }

// Function for the previous song button
function previousSong() {
  // If the length of songCache is 1, we reload the current song
  if (songCache.length == 1) {
    highlightCurrentSong(songCache[songCache.length - 1])
    audio.src = songCache[songCache.length - 1]
    audio.play()
  }
  // If the length of songCache is greater than 1, there are previously played songs
  else if (songCache.length > 1) {
    songCache.pop() // Removing currently playing song
    highlightCurrentSong(songCache[songCache.length - 1])
    audio.src = songCache[songCache.length - 1]
    audio.play()
    setSongName(decodeURIComponent(songCache[songCache.length - 1]))
    ipc.send("getAlbumCover", decodeURIComponent(songCache[songCache.length - 1]))
  }
}

// Function for the shuffle button
function toggleShuffle() {
  let shuffleButton = document.getElementById("shuffle")
  if (shuffle == 0) {
    shuffle = 1
    shuffleButton.style.background = "#7393B3"
    shuffleButton.src = "img/shuffleHover.png"
  } else {
    shuffle = 0
    shuffleButton.style.background = "none"
    shuffleButton.src = "img/shuffle.png"
  }
}

// Function for the next song button
function nextSong() {
  if (songCache.length > 0) {
    // Grabbing the directory of the last non-queued song
    let currentSongDirectory = songCache[songCache.length - 1]
    let name = null
    let directory = null
    for (var i = (currentSongDirectory.length - 1); i >= 0; i--) {
      if (currentSongDirectory[i] == '/' || currentSongDirectory[i] == '\\') {
        name = currentSongDirectory.substr(i + 1)
        name = decodeURIComponent(name)
        directory = currentSongDirectory.substr(0, i + 1)
        break
      }
    }

    let files = fs.readDirectory(directory)

    let nextSongDirectory = directory
    if (queue.length > 0) {
      nextSongDirectory = queue[queue.length - 1]
      queue.pop()
    } else if (shuffle == 0) {
      if (files.indexOf(name) == (files.length - 1))
        nextSongDirectory += encodeURIComponent(files[0])
      else
        nextSongDirectory += encodeURIComponent(files[files.indexOf(name) + 1])
      songCache.push(nextSongDirectory)
    } else {
      let nextSongIndex = null
      while (true) {
        nextSongIndex = Math.floor(Math.random() * files.length)
        if (nextSongIndex != files.indexOf(name)) break
      } nextSongDirectory += encodeURIComponent(files[nextSongIndex])
      songCache.push(nextSongDirectory)
    }

    highlightCurrentSong(nextSongDirectory)
    audio.src = nextSongDirectory
    audio.play()
    setSongName(decodeURIComponent(nextSongDirectory))
    ipc.send("getAlbumCover", decodeURIComponent(nextSongDirectory))
  }
}

function youtubeToMP3() {
  // Div box with input
  let youtubeToMP3 = document.getElementById("youtubeToMP3")
  if (window.getComputedStyle(youtubeToMP3).display == "none") {
    youtubeToMP3.style.display = "block"
    document.getElementById("youtubeToMP3Input").focus()
    document.getElementById("controls").style.display = "none"
  } else youtubeToMP3.style.display = "none"
}

// Sends an IPC request to convert the link in #youtubeToMP3Input
function convertYoutubeLink() {
  let youtubeLink = document.getElementById("youtubeToMP3Input").value
  if (youtubeLink.length != 0) {
    document.getElementById("youtubeToMP3").style.display = "none"
    // Getting directory to convert the video to
    ipc.send("getDirectory", youtubeLink)
  }
}
// Fires convertYoutubeLink() on enter press
document.addEventListener("keydown", () => {
  if (event.key == "Enter") convertYoutubeLink()
})

// Change position of song through #songSlider
function changeSongPosition(newPosition) { audio.currentTime = newPosition }

// Change volume through #volumeSlider
function changeVolume(newVolume) { audio.volume = newVolume / 100 }
