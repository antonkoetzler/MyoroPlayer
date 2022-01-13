#include "MusicSelector.h"

MusicSelector::MusicSelector(wxFrame* parent) : wxBoxSizer(wxHORIZONTAL)
{
  songlist = new SongList(parent);
  Add(songlist, 1, wxEXPAND);
}
