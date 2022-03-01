#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, SONGLIST)
{
  // Initialization
  #ifdef linux
    directory = new wxDir("../songs/");
  #endif
  #ifdef _WIN32
    directory = new wxDir("..\\songs/");
  #endif

  // Exiting if the directory wasn't opened
  if (!directory->IsOpened()) 
  {
    std::cout << "!directory->IsOpened()" << std::endl;
    exit(1);
  }

  // Loading the directory's songs
  wxString fileName;
  wxString fileExtension;
  bool get = directory->GetFirst(&fileName, wxEmptyString, wxDIR_FILES);
  while (get)
  {
    // Getting the file extension
    for (int i = (fileName.length() - 1); i >= 0; i--)
    {
      if (fileName[i] == '.')
      {
        fileExtension = fileName.substr(i + 1);

        // Checking if the fileExtension is appropriate
        for (int i = 0; i < 3; i++)
          if (fileExtension[i] == allowedExtensions[i])
            break;

        Append(fileName);

        break;
      }
    }

    get = directory->GetNext(&fileName);
  }
}

SongList::SongList(wxFrame* parent, wxString playlistDirectoryArg) : wxListBox(parent, SONGLIST)
{
  playlistDirectory = playlistDirectoryArg;
  #ifdef linux
    if (playlistDirectory[playlistDirectory.length() - 1] != '/')
      playlistDirectory += '/';
  #endif
  #ifdef _WIN32
    if (playlistDirectory[playlistDirectory.length() - 1] != '\\')
      playlistDirectory += '\\';
  #endif

  // Initialization
  #ifdef linux
    directory = new wxDir(playlistDirectory);
  #endif
  #ifdef _WIN32
    directory = new wxDir(playlistDirectory);
  #endif

  // Exiting if the directory wasn't opened
  if (!directory->IsOpened()) 
  {
    std::cout << "!directory->IsOpened()" << std::endl;
    exit(1);
  }

  // Loading the directory's songs
  wxString fileName;
  wxString fileExtension;
  bool get = directory->GetFirst(&fileName, wxEmptyString, wxDIR_FILES);

  while (get)
  {
    // Getting file extension
    for (int i = (fileName.length() - 1); i >= 0; i--)
      if (fileName[i] == '.')
        fileExtension = fileName.substr(i + 1);
    fileExtension = fileExtension.MakeUpper();

    for (int i = 0; i < 3; i++)
    {
      if (fileExtension == allowedExtensions[i])
      {
        Append(fileName);
        break;
      }
    }

    get = directory->GetNext(&fileName);
  }
}

wxString SongList::getDirectory() { return playlistDirectory; }
