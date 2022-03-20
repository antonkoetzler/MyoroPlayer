#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, SONGLIST)
{
  playlistDirectory = wxGetCwd();
  #ifdef linux
    playlistDirectory += "/songs/";
  #endif
  #ifdef _WIN32
    playlistDirectory += "\\songs\\";
  #endif
  loadSongs();
}

SongList::SongList(wxFrame* parent, wxString playlistDirectoryArg) : wxListBox(parent, SONGLIST)
{
  playlistDirectory = playlistDirectoryArg;
  #ifdef linux
    if (playlistDirectory != '/') playlistDirectory += '/';
  #endif
  #ifdef _WIN32
    if (playlistDirectory != '\\') playlistDirectory += '\\';
  #endif
  loadSongs();
}

void SongList::loadSongs()
{
  directory = new wxDir(playlistDirectory);
  if (!directory->IsOpened())
  {
    delete directory; directory = nullptr;

    playlistDirectory = wxGetCwd();
    #ifdef linux
      playlistDirectory += "/songs/";
    #endif
    #ifdef _WIN32
      playlistDirectory += "\\songs\\";
    #endif

    directory = new wxDir(playlistDirectory);

    if (!directory->IsOpened()) { exit(1); }
  }

  wxString fileName;
  bool cont = directory->GetFirst(&fileName, wxEmptyString, wxDIR_FILES);
  while (cont)
  {
    // Getting the file extension
    wxString fileExtension = wxEmptyString;
    for (int i = (fileName.length() - 1); i >= 0; i--)
      if (fileName[i] == '.')
        fileExtension = fileName.substr(i + 1);
    fileExtension.MakeUpper();

    if (fileExtension == "MP3" || fileExtension == "AAC")
      Append(fileName);

    cont = directory->GetNext(&fileName);
  }

  delete directory; directory = nullptr;
}

wxString SongList::getPlaylistDirectory() { return playlistDirectory; }

