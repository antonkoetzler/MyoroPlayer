#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, SONGLIST)
{
  // Loads songs from the ${PROJECT_DIR}/songs
  #ifdef linux
    directory = new wxDir("../songs/");
  #endif
  #ifdef _WIN32
    directory = new wxDir("..\\songs\\");
  #endif

  // Making sure the directory is opened
  if (!directory->IsOpened())
  {
    std::cout << "!directory->IsOpened() SongList::SongList" << std::endl;
    exit(1);
  }

  // Starts traversing directory
  wxString fileName;
  bool cont = directory->GetFirst(
    &fileName,
    wxEmptyString,
    wxDIR_FILES
  );

  // Checking every file and there extension,
  // then appending said file to the playlist
  wxString fileExtension = wxEmptyString;
  while (cont)
  {
    // Getting the file extension
    for (int i = (fileName.length() - 1); i >= 0; i--)
    {
      if (fileName[i] == '.')
      {
        fileExtension = fileName.substr(i + 1);
        fileExtension.MakeUpper();
        break;
      }
    }

    if (fileExtension != wxEmptyString && fileExtension == "MP3")
      Append(fileName);

    fileExtension = wxEmptyString;
    cont = directory->GetNext(&fileName);
  }

  // Save memory
  delete directory; directory = nullptr;
}
