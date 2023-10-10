#ifndef MUSICLIBRARY_FILEMANAGER_HPP
#define MUSICLIBRARY_FILEMANAGER_HPP

#include <filesystem>
#include <vector>
#include <iostream>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>

namespace fs = std::filesystem;

class FileManager
{
    fs::path directory;
    std::vector<std::string> oggFilePaths;

public:
    FileManager();
    void scanDirectory();
    void changeScanningDirectory(fs::path &newDirectory);
    void printOggFilePaths();

    std::vector<std::string> &getOggFilePaths();
};

#endif