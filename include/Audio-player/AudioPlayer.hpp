#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_AUDIOPLAYER_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_AUDIOPLAYER_HPP

#include <deque>
#include <memory>
#include <mutex>
#include <random>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include "Album.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

class AudioPlayer {
  public:
    using songsVector = std::vector<std::shared_ptr<Song>>;

    AudioPlayer() = default;

    void loadSound2Queue(int &whichItem, songsVector &vec);

    void loadSound2Queue(int &whichItem, std::vector<Album> &vec);

    void playQueue();

    bool isDequeEmpty();

    sf::Music &getCurrentMusic();

    bool checkMusicPlaying();

    void pauseOrResumeMusic(sf::Music &music);

    void advanceForwardMusic(sf::Music &music);

    void advanceBackwardMusic(sf::Music &music);

    void stopMusic(sf::Music &music);

    void shuffleQueue();

    sf::Time &getCurrentTime();

    float calculateSongProgressBar(sf::Music &music);

    std::deque<std::shared_ptr<Song>> &getSongQueue() { return songQueue; }

    std::shared_ptr<Song> &getSongQueueFront() { return songQueue.front(); }

  private:
    sf::Music music;
    std::deque<std::shared_ptr<Song>> songQueue;
    std::mutex musicMutex;
    sf::Time currentTime;
};

#endif