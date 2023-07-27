#ifndef MUSICLIBRARY_SONG_H
#define MUSICLIBRARY_SONG_H

#include <string>
#include <iostream>

class Song {
protected:
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    int year;
    int duration;

public:
    Song() = default;
    Song(std::string title, std::string artist, std::string album, std::string genre,
         int year, int duration);

    const std::string &getTitle() const;
    void setTitle(const std::string &title);
    const std::string &getArtist() const;
    void setArtist(const std::string &artist);
    const std::string &getAlbum() const;
    void setAlbum(const std::string &album);
    const std::string &getGenre() const;
    void setGenre(const std::string &genre);
    int getYear() const;
    void setYear(int year);
    int getDuration() const;
    void setDuration(int duration);

    void createSong();
    friend std::ostream& operator<<(std::ostream& os, const Song& song);

    bool operator<(const Song& s1) const;
};


#endif //MUSICLIBRARY_SONG_H
