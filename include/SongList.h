#pragma once

#include <wx/wx.h>
#include <wx/dir.h>

enum { SONGLIST };

class SongList : public wxListBox
{
 public:
  SongList(wxFrame*);
  SongList(wxFrame*, wxString);

  wxString getDirectory();

 private:
  wxDir* directory;
  wxString allowedExtensions[3] = {"MP3", "AAC", "WAV"};
  #ifdef linux
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/";
  #endif
  #ifdef _WIN32
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\";
  #endif
};
