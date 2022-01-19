#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
  dir = new wxDir("../songs/");

  if (dir->IsOpened()) std::cout << "Working" << std::endl;
  else std::cout << "Not Working" << std::endl;
}
