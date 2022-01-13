#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "Interface.h"

class Frame : public wxFrame
{
public:
  Frame();

private:
  MenuBar* menubar;
  Interface* interface;
};
