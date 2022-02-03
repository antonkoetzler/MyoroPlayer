#pragma once

#include <wx/wx.h>
#include <wx/dir.h>

class SongList : public wxListBox
{
 public:
  SongList(wxWindow*);

  // Makes sure the wxString& is an audio file and
  // changes the wxString& to just the song name
  // without the file extension
  bool checkExtension(wxString&);

 private:
  wxDir* dirReader;
  wxMessageDialog* errorMessage;
};
