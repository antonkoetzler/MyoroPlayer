#include "SongList.h"

SongList::SongList(wxWindow* parent) : wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_MULTIPLE | wxLB_EXTENDED | wxLB_SORT)
{
  Append("Hello World");
}
