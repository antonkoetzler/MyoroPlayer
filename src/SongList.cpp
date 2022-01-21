#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
  readDirectory("../songs/");
}

void SongList::readDirectory(std::string directory)
{
  dir = new wxDir(directory);

  if (!dir->IsOpened())
  {
    errorMessage = new wxMessageDialog(
      nullptr,
      "Invalid directory given"
    );
    errorMessage->ShowModal();
    delete errorMessage; errorMessage = nullptr;
    return;
  }

  wxString filename;
  bool found = dir->GetFirst(
    &filename,
    wxEmptyString,
    wxDIR_FILES
  );
  std::string* filenameSplit = nullptr;
  std::string allowedFiletypes[8] = {
    "MP3", "AAC", "WAV",
    "WMA", "FLAC", "AIFF"
  };

  while (found)
  {
    filenameSplit = splitFilename(filename);
    if (filenameSplit != nullptr)
    {
      // Making sure the file extension is appropriate
      for (int i = 0; i < 8; i++)
        if (allowedFiletypes[i] == filenameSplit[1])
          Append(filenameSplit[0]);
    }
    found = dir->GetNext(&filename);
  }
}

std::string* SongList::splitFilename(wxString filename)
{
  // Getting the file extension
  for (int i = (filename.length() - 1); i >= 0; i--)
  {
    if (filename[i] == '.')
    {
      std::string* returnVariable = new std::string[2];

      // Adding file name and extension
      returnVariable[0] = filename.substr(0, i);  // File name

      returnVariable[1] = filename.substr(i + 1); // File extension
      for (auto& i : returnVariable[1]) i = toupper(i);

      return returnVariable;
    }
  }

  return nullptr;
}
