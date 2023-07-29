#ifndef MUSICLIBRARY_PLAYLIST_H
#define MUSICLIBRARY_PLAYLIST_H

#include <string>
#include <vector>
#include <memory>
#include "Song.h"

class Playlist : public Song{
    std::vector<std::shared_ptr<Song>> playlistSongs;

public:
    Playlist() = default;
    Playlist(std::string title, const std::string& artist, const std::vector<std::shared_ptr<Song>>& playlistSongs);
    Playlist createPlaylist();

    static bool compareByDuration(const Playlist& p1, const Playlist& p2);
    static bool compareByTitle(const Playlist& p1, const Playlist& p2);
    static bool compareByCreator(const Playlist& p1, const Playlist& p2);
    static bool compareByYear(const Playlist& p1, const Playlist& p2);

    void addSongToPlaylist(const Song& song, std::string playlistTitle, std::vector<Song> playlistSongs);
    void removeSongFromPlaylist(const std::string& songTitle);

};


#endif //MUSICLIBRARY_PLAYLIST_H
