#include "SongList.h"

SongList::SongList(wxWindow* parent) : wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_EXTENDED | wxLB_SORT)
{
  for (int i = 0; i < 10; i++) Append("Hello");
}
