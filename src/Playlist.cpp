#include "../include/Audio-player/Playlist.hpp"

Playlist::Playlist(
    const std::string &title, const std::string &creator,
    songsVector &playlistSongs, std::tm year) {
    name = title;

    char *envUsername = std::getenv("USERNAME");
    if (envUsername != nullptr) {
        this->creator = envUsername;
    } else {
        this->creator = "Unknown";
    }

    this->playlistSongs = playlistSongs;

    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    year = *std::localtime(&now_time);
    this->year = year;
}

Playlist::Playlist(const std::string &title) { name = title; }

Playlist::Playlist(const Playlist &otherPlaylist)
    : playlistSongs(otherPlaylist.playlistSongs) {
    std::copy(
        otherPlaylist.playlistSongs.begin(), otherPlaylist.playlistSongs.end(),
        playlistSongs.begin());
    name = otherPlaylist.name;
    creator = otherPlaylist.creator;
    year = otherPlaylist.year;
}

Playlist &Playlist::operator=(const Playlist &otherPlaylist) {
    if (this == &otherPlaylist) {
        return *this;
    }
    std::copy(
        otherPlaylist.playlistSongs.begin(), otherPlaylist.playlistSongs.end(),
        playlistSongs.begin());
    name = otherPlaylist.name;
    creator = otherPlaylist.creator;
    year = otherPlaylist.year;

    return *this;
}

bool Playlist::compareByDuration(const Playlist &p1, const Playlist &p2) {
    return p1.duration < p2.duration;
}

bool Playlist::compareByTitle(const Playlist &p1, const Playlist &p2) {
    return p1.name < p2.name;
}

bool Playlist::compareByCreator(const Playlist &p1, const Playlist &p2) {
    return p1.creator < p2.creator;
}

bool Playlist::compareByYear(const Playlist &p1, const Playlist &p2) {
    std::tm tm1 = p1.year;
    std::tm tm2 = p2.year;

    if (tm1.tm_year != tm2.tm_year) {
        return tm1.tm_year < tm2.tm_year;
    } else if (tm1.tm_mon != tm2.tm_mon) {
        return tm1.tm_mon < tm2.tm_mon;
    } else {
        return tm1.tm_mday < tm2.tm_mday;
    }
}

void Playlist::addSongToPlaylist(
    const std::shared_ptr<Song> &song, const std::string &playlistTitle,
    std::vector<Song> &_playlistSongs) {
    playlistSongs.push_back(song);
}

void Playlist::removeSongFromPlaylist(const std::string &songTitle) {
    for (auto &playlistSong : playlistSongs) {
        if (playlistSong->getTitle() == songTitle) {
            playlistSongs.erase(playlistSongs.begin());
        }
    }
}

u_int Playlist::calculateDuration() {
    u_int duration = 0;
    for (const auto &song : playlistSongs) {
        duration += song->getDuration();
    }
    return duration;
}
