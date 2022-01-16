#pragma once

#include <wx/wx.h>

class About : public wxDialog
{
public:
  About();

  // So that the whole program will close properly after closing the dialog window
  virtual void OnClose(wxCloseEvent&);

private:
  wxStaticText* message;
  wxBitmap bitmap; // Image being processed
  wxStaticBitmap* image; // Actual image on the screen
  wxBoxSizer* sizer;
};
