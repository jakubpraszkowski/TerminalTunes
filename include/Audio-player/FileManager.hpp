#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_FILEMANAGER_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_FILEMANAGER_HPP

#include <sys/inotify.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

namespace fs = std::filesystem;

constexpr int EVENT_SIZE = sizeof(struct inotify_event);
constexpr int EVENT_BUF_LEN = 1024 * (EVENT_SIZE + 16);

class FileManager {
  public:
    FileManager();

    void scanDirectory();

    void changeScanningDirectory(fs::path &newDirectory);

    void printOggFilePaths();

    std::vector<std::string> &getOggFilePaths();

    void saveFilePaths();

    void loadFilePaths();

    bool checkForChanges();

    fs::path &getDirectory();

  private:
    fs::path directory;

    std::vector<std::string> oggFilePaths;
};

#endif