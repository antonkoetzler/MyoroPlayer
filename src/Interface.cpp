#include "Interface.h"

Interface::Interface(wxFrame* parent) : wxBoxSizer(wxVERTICAL)
{
  musicselector = new MusicSelector(parent);
  Add(musicselector, 1, wxEXPAND);

  musiccontrols = new MusicControls(parent);
  Add(musiccontrols, 0, wxFIXED_MINSIZE | wxEXPAND);
}
