#pragma once

#include <wx/wx.h>
#include "Frame.h"

class App : public wxApp
{
 public:
  virtual bool OnInit();

 private:
  Frame* window;
};

