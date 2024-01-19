#include "../include/Audio-player/Song.hpp"

Song::Song(
    const std::string &name, const std::string &creator,
    const std::string &album, const std::string &genre, u_int year,
    int duration, const std::string &path) {
    this->name = name;
    this->creator = creator;
    this->album = album;
    this->genre = genre;
    this->year = year;
    this->duration = duration;
    this->path = path;
}

Song::Song(const std::string &name, int duration) {
    this->name = name;
    this->duration = duration;
}

const std::string &Song::getTitle() const { return name; }

const std::string &Song::getArtist() const { return creator; }

const std::string &Song::getAlbum() const { return album; }

const std::string &Song::getGenre() const { return genre; }

const u_int Song::getYear() const { return year; }

const int Song::getDuration() const { return duration; }

const std::string &Song::getPath() const { return path; }

bool Song::compareByDuration(const Song &s1, const Song &s2) {
    return s1.duration < s2.duration;
}

bool Song::compareByTitle(const Song &s1, const Song &s2) {
    return s1.name < s2.name;
}

bool Song::compareByArtist(const Song &s1, const Song &s2) {
    return s1.creator < s2.creator;
}

bool Song::compareByAlbum(const Song &s1, const Song &s2) {
    return s1.album < s2.album;
}

bool Song::compareByGenre(const Song &s1, const Song &s2) {
    return s1.genre < s2.genre;
}

bool Song::compareByYear(const Song &s1, const Song &s2) {
    return s1.year < s2.year;
}