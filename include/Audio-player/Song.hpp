#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_SONG_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_SONG_HPP

#include <string>

class Song {
  public:
    Song() = default;

    Song(
        const std::string &title, const std::string &artist,
        const std::string &album, const std::string &genre, unsigned int year,
        int duration, const std::string &path);

    Song(const std::string &title, int duration);

    const std::string &getTitle() const;

    const std::string &getArtist() const;

    const std::string &getAlbum() const;

    const std::string &getGenre() const;

    const unsigned int getYear() const;

    const int getDuration() const;

    const std::string &getPath() const;

    static bool compareByDuration(const Song &s1, const Song &s2);

    static bool compareByTitle(const Song &s1, const Song &s2);

    static bool compareByArtist(const Song &s1, const Song &s2);

    static bool compareByAlbum(const Song &s1, const Song &s2);

    static bool compareByGenre(const Song &s1, const Song &s2);

    static bool compareByYear(const Song &s1, const Song &s2);

  protected:
    std::string name;
    std::string creator;
    unsigned int size;
    unsigned int duration;
    std::string album;

  private:
    std::string genre;
    unsigned int year = 0;
    std::string path;
};

#endif // MUSICLIBRARY_SONG_HPP
