#pragma once

#include <wx/wx.h>
#include <wx/dir.h>

enum { SONGLIST };

class SongList : public wxListBox
{
 public:
  SongList(wxFrame*);
  SongList(wxFrame*, wxString);

  void loadSongs();

  wxString getPlaylistDirectory();

 private:
  wxDir* directory;
  wxString playlistDirectory;
};

