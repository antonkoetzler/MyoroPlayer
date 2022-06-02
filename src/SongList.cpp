#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, wxID_ANY)
{
  Append("Hello");
}
