#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_ALBUM_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_ALBUM_HPP

#include <memory>
#include <string>
#include <vector>

#include "Song.hpp"

class Album : public Song {
  public:
    using songsVector = std::vector<std::shared_ptr<Song>>;

    Album() = default;

    Album(const std::string &album_name);

    songsVector &getAlbumSongs();

    void addSong(std::shared_ptr<Song> song);

  private:
    songsVector songsInAlbum;
};

#endif // MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_ALBUM_HPP