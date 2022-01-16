#include "About.h"

About::About() : wxDialog(nullptr, wxID_ANY, "About MyoroPlayer")
{
  SetBackgroundColour(wxColour(255, 182, 193));

  // Making sure that the window closes properly and it's pointer gets deleted
  this->Bind(wxEVT_CLOSE_WINDOW, &About::OnClose, this);

  // Setting the image in the window
  bitmap.LoadFile("../img/aboutLogo.png", wxBITMAP_TYPE_PNG);
  if (bitmap.IsOk())
    image = new wxStaticBitmap(
      this,
      wxID_ANY,
      bitmap
    );

  // Setting the message
  message = new wxStaticText(
    this,
    wxID_ANY,
    "\n(2022)\n\n A libre MP3 player with youtube2mp3 capabilities! \n\n Author: Anton Koetzler-Faust \n Email: antonkoetzler-faust@hotmail.com",
    wxDefaultPosition,
    wxDefaultSize,
    wxALIGN_CENTRE_HORIZONTAL
  );
  message->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  message->SetForegroundColour(wxColour(0, 0, 0));

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(
    image,
    0,
    wxFIXED_MINSIZE | wxALIGN_CENTER
  );
  sizer->Add(
    message,
    0,
    wxALIGN_CENTER
  );

  SetSizerAndFit(sizer);
}

void About::OnClose(wxCloseEvent& evt) { delete this; }
