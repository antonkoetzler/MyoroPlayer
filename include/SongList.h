#pragma once

#include <wx/wx.h>
#include <wx/dir.h>

class SongList : public wxListBox
{
public:
  SongList(wxFrame*);

private:
  wxDir* dir;
};
