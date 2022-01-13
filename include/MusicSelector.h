#pragma once

#include <wx/wx.h>
#include "SongList.h"

class MusicSelector : public wxBoxSizer
{
public:
  MusicSelector(wxFrame*);

private:
  SongList* songlist;
};
