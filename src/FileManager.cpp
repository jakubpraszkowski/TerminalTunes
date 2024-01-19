#include "../include/Audio-player/FileManager.hpp"

FileManager::FileManager() { directory = "/home/kubuski/Music"; }

void FileManager::scanDirectory() {
    for (fs::recursive_directory_iterator it(directory), end; it != end; it++) {
        if (fs::is_regular_file(*it) && it->path().extension() == ".ogg") {
            oggFilePaths.push_back(it->path().string());
        }
    }
}

void FileManager::changeScanningDirectory(fs::path &newDirectory) {
    this->directory = newDirectory;
}

void FileManager::printOggFilePaths() {
    int i = 0;
    for (const auto &path : oggFilePaths) {
        std::cout << path << std::endl;
        i++;
    }
    std::cout << "Totall:" << i;
}

std::vector<std::string> &FileManager::getOggFilePaths() {
    return oggFilePaths;
}

void FileManager::saveFilePaths() {
    std::ofstream file("filepaths.txt");
    for (const auto &path : oggFilePaths) {
        file << path << std::endl;
    }
    file.close();
}

void FileManager::loadFilePaths() {
    std::ifstream file("filepaths.txt");
    std::string line;
    while (std::getline(file, line)) {
        oggFilePaths.push_back(line);
    }
    file.close();
}

bool FileManager::checkForChanges() { return false; }

fs::path &FileManager::getDirectory() { return directory; }
