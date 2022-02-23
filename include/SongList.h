#pragma once

#include <wx/wx.h>
#include <wx/dir.h>

enum { SONGLIST };

class SongList : public wxListBox
{
 public:
  SongList(wxFrame*);

 private:
  wxDir* directory;
  wxString allowedExtensions[3] = {"MP3", "AAC", "WAV"};
};
