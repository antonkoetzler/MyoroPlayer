// Dependancies: ffmpeg, youtube-dl
// - Installing ffmpeg on Windows: https://www.geeksforgeeks.org/how-to-install-ffmpeg-on-windows/
// - Installing ffmpeg on linux (Ubuntu example): sudo apt install ffmpeg
// - Installing youtube-dl on windows: https://youtube-dl.org/
//   - Add this entire directory as an environment variable
// - Installing youtube-dl on linux (Ubuntu example): sudo apt install youtube-dl
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  // Help screen
  if (argc == 1)
  {
    #ifdef linux
      system("clear");
    #endif
    #ifdef _WIN32
      system("cls");
    #endif

    std::cout << "yt2mp3 <YT directory>\n";
    std::cout << "- Extracts MP3 of <YT directory> into current directory\n\n";
    std::cout << "yt2mp3 <YT directory> <computer directory>\n";
    std::cout << "- Extracts MP3 of <YT directory> into <computer directory>\n";
  }
  // Convert YouTube link into current directory
  else if (argc == 2)
  {
    std::string link = argv[1]; // Converting to a string
    std::string command = "youtube-dl --extract-audio --audio-format mp3 " + link;
    system(command.c_str());
  }
  // Convert YouTube link into specific directory
  else if (argc == 3)
  {
    std::string link = argv[1];
    std::string directory = argv[2];
    if (directory[directory.length() - 1] != '/') directory += '/';
    std::string command = "youtube-dl --extract-audio --audio-format mp3 -o \"" + directory + "%(title)s.%(ext)s\" " + link;
    system(command.c_str());
  }

  return 0;
}
