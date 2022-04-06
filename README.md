# MyoroPlayer
A libre MP3 player with Youtube to MP3

# Installing
## Installing with an installer
1. Go to: https://github.com/antonkoetzler/MyoroPlayer/releases/tag/1.0
  - Support for Windows & Ubuntu
2. Download an installer appropriate to your operating system
3. Linux installation
  - Download MyoroPlayerUbuntu.zip **to your downloads directory**
  - `unzip MyoroPlayerUbuntu.zip; cd MyoroPlayerUbuntu; sh Ubuntu\ Install.sh`
  - Enter your password, as the script installs the package youtube-dl
  - Done.
## Installing by source
- Prerequisites
  1. CMake
  2. A C++ compiler
  3. Compiled wxWidgets source
    - Instructions for Windows & Ubuntu: https://github.com/antonkoetzler/wxWidgets/tree/main/Installation
1. `git clone git@github.com:antonkoetzler/MyoroPlayer.git`
2. `cd MyoroPlayer`
3. Windows: `cmake -G "MinGW Makefiles" -S ./ -B ./build; cd build; mingw32-make`
4. Linux: `cmake -G "Unix Makefiles" -S ./ -B ./build; cd build; make`
5. Now you can place the executable & the songs folder into a folder and place wherever

# Troubleshooting
## Linux
1. If your MyoroPlayer is not working, make sure `build-essential` and `libgtk-3-dev` are installed

Inspired by Audacity
