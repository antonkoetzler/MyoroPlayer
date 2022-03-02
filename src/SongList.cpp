#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListCtrl(parent, wxID_ANY)
{
  wxListItem foo;
  foo.SetId(500);
  foo.SetText("Hello");

  InsertItem(foo);
}
