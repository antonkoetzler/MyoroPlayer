#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, SONGLIST)
{
  wxString playlistDirectory = wxGetCwd();
  #ifdef linux
    playlistDirectory += "/songs/";
  #endif
  #ifdef _WIN32
    playlistDirectory += "\\songs\\";
  #endif

  directory = new wxDir(playlistDirectory);
  if (!directory->IsOpened()) { Close(); }

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
}

