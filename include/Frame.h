#pragma once

#include <wx/wx.h>
#include "SongList.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

 private:
  // Sizer for dividing song list, music controls, etc
  wxBoxSizer* ui;
  SongList* sl; // sl = song list
                // On Windows, you cannot set the var name to songlist
};

