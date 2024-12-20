#pragma once

#include <stdexcept>
#include <string>

#include <SFML/Audio.hpp>

class Song {
  public:
    Song() = default;
    Song(
        const std::string &title, const std::string &artist,
        const std::string &album, const std::string &genre, unsigned int year,
        int duration, const std::string &path);
    Song(const std::string &title, const std::string &file_path, int duration);
    Song(const std::string &title, int duration);

    const std::string &get_title() const;
    const std::string &get_artist() const;
    const std::string &get_album() const;
    const std::string &get_genre() const;
    unsigned int get_year() const;
    int get_duration() const;
    const std::string &get_path() const;

    static bool CompareByDuration(const Song &s1, const Song &s2);
    static bool CompareByTitle(const Song &s1, const Song &s2);
    static bool CompareByArtist(const Song &s1, const Song &s2);
    static bool CompareByAlbum(const Song &s1, const Song &s2);
    static bool CompareByGenre(const Song &s1, const Song &s2);
    static bool CompareByYear(const Song &s1, const Song &s2);

  protected:
    std::string title_;
    std::string artist_;
    unsigned int duration_ = 0;
    std::string album_;
    std::string genre_;
    unsigned int year_ = 0;
    std::string path_;
};
