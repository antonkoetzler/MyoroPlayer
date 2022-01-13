#pragma once

#include <wx/wx.h>
#include "MusicSelector.h"
#include "MusicControls.h"

class Interface : public wxBoxSizer
{
public:
  Interface(wxFrame*);

private:
  MusicSelector* musicselector;
  MusicControls* musiccontrols;
};
