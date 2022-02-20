#include "SongList.h"

SongList::SongList(wxWindow* parent) : wxListBox(parent, SONGLIST, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_EXTENDED | wxLB_SORT)
{
  dirReader = new wxDir("../songs/");

  if (!dirReader->IsOpened())
  {
    errorMessage = new wxMessageDialog(
      this,
      "Error opening directory",
      wxEmptyString,
      wxOK
    );
    errorMessage->ShowModal();
  }
  else
  {
    wxString fileName;
    bool cont = dirReader->GetFirst(
      &fileName,
      wxEmptyString,
      wxDIR_FILES
    );

    while (cont)
    {
      // Making sure it's an audio file
      if (checkExtension(fileName))
        Append(fileName);
      cont = dirReader->GetNext(&fileName);
    }
  }
}

bool SongList::checkExtension(wxString& fileName)
{
  for (int i = (fileName.length() - 1); i >= 0; i--)
  {
    if (fileName[i] == '.')
    {
      wxString fileExtension = fileName.substr(i + 1);

      // Making fileExtension lowercase
      for (int i = 0; i < fileExtension.length(); i++)
        fileExtension[i] = tolower(fileExtension[i]);

      if (fileExtension == "mp3" || fileExtension == "wav"
        || fileExtension == "flac" || fileExtension == "aac")
        return true;
      else
        return false;
    }
  }

  return false;
}
