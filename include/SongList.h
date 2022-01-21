#pragma once

#include <string>
#include <wx/wx.h>
#include <wx/dir.h>

class SongList : public wxListBox
{
public:
  SongList(wxFrame*);
  void readDirectory(std::string);
  // Returns an array with file name & extension
  // seperated, nullptr if there is no extension
  std::string* splitFilename(wxString);

private:
  wxDir* dir = nullptr;
  wxMessageDialog* errorMessage;
};
