#include "../src/Album.cpp"
#include "../src/Song.cpp"
#include <gtest/gtest.h>
#include <memory>

class AlbumTest : public ::testing::Test, public Song {
  public:
    bool operator==(const Album &rhs) const {
        return getTitle() == rhs.getTitle();
    }
    bool operator==(const Song &rhs) const {
        return getTitle() == rhs.getTitle() && getArtist() == rhs.getArtist() &&
               getAlbum() == rhs.getAlbum() && getGenre() == rhs.getGenre() &&
               getYear() == rhs.getYear() &&
               getDuration() == rhs.getDuration() && getPath() == rhs.getPath();
    }

  protected:
    std::shared_ptr<Song> expectedSong1 = std::make_shared<Song>("Song1", 200);
    std::shared_ptr<Song> expectedSong2 = std::make_shared<Song>("Song2", 200);
    std::shared_ptr<Song> expectedSong3 = std::make_shared<Song>(
        "Title1", "Creator1", "Album", "Country", 1997, 2000, "~/nice");
    Album album = Album("Test Album");
};

TEST_F(AlbumTest, TestAlbumName) { EXPECT_EQ(album.getTitle(), "Test Album"); }

TEST_F(AlbumTest, TestAddSong) {
    album.addSong(expectedSong1);
    EXPECT_EQ(album.getAlbumSongs().size(), 1);
    EXPECT_EQ(album.getAlbumSongs()[0]->getTitle(), "Song1");
}

TEST_F(AlbumTest, TestMultipleAddSong) {
    album.addSong(expectedSong1);
    album.addSong(expectedSong2);
    EXPECT_EQ(album.getAlbumSongs().size(), 2);
    EXPECT_EQ(album.getAlbumSongs()[0]->getTitle(), "Song1");
    EXPECT_EQ(album.getAlbumSongs()[1]->getTitle(), "Song2");
}

TEST_F(AlbumTest, TestDifferentConstuctors) {
    album.addSong(expectedSong1);
    album.addSong(expectedSong3);
    EXPECT_EQ(album.getAlbumSongs().size(), 2);
    EXPECT_EQ(album.getAlbumSongs()[1], expectedSong3);
}