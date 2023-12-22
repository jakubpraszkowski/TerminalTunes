#include "../include/Audio-player/Album.hpp"

Album::Album(const std::string &album_name) { name = album_name; }

Album::songsVector &Album::getAlbumSongs() { return songsInAlbum; }

void Album::addSong(std::shared_ptr<Song> song) {
    songsInAlbum.push_back(song);
}