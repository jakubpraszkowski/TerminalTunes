// #include "../src/Song.cpp"
#include "../../include/Audio-player/Song.hpp"

#include <gtest/gtest.h>

class SongComparisonTest : public ::testing::Test {
  protected:
    Song song1{"Title1", "Artist1", "Album1", "Genre1", 2000, 180, "Path1"};
    Song song2{"Title2", "Artist2", "Album2", "Genre2", 2001, 200, "Path2"};
};

TEST_F(SongComparisonTest, CompareByDuration) {
    EXPECT_TRUE(Song::CompareByDuration(song1, song2));
    EXPECT_FALSE(Song::CompareByDuration(song2, song1));
}

TEST_F(SongComparisonTest, CompareByTitle) {
    EXPECT_TRUE(Song::CompareByTitle(song1, song2));
    EXPECT_FALSE(Song::CompareByTitle(song2, song1));
}

TEST_F(SongComparisonTest, CompareByArtist) {
    EXPECT_TRUE(Song::CompareByArtist(song1, song2));
    EXPECT_FALSE(Song::CompareByArtist(song2, song1));
}

TEST_F(SongComparisonTest, CompareByAlbum) {
    EXPECT_TRUE(Song::CompareByAlbum(song1, song2));
    EXPECT_FALSE(Song::CompareByAlbum(song2, song1));
}

TEST_F(SongComparisonTest, CompareByGenre) {
    EXPECT_TRUE(Song::CompareByGenre(song1, song2));
    EXPECT_FALSE(Song::CompareByGenre(song2, song1));
}

TEST_F(SongComparisonTest, CompareByYear) {
    EXPECT_TRUE(Song::CompareByYear(song1, song2));
    EXPECT_FALSE(Song::CompareByYear(song2, song1));
}

TEST_F(SongComparisonTest, TestTitle) {
    EXPECT_EQ(song1.get_title(), "Title1");
}

TEST_F(SongComparisonTest, TestArtist) {
    EXPECT_EQ(song1.get_artist(), "Artist1");
}

TEST_F(SongComparisonTest, TestAlbum) {
    EXPECT_EQ(song1.get_album(), "Album1");
}

TEST_F(SongComparisonTest, TestGenre) {
    EXPECT_EQ(song1.get_genre(), "Genre1");
}

TEST_F(SongComparisonTest, TestYear) { EXPECT_EQ(song1.get_year(), 2000); }

TEST_F(SongComparisonTest, TestDuration) {
    EXPECT_EQ(song1.get_duration(), 180);
}

TEST_F(SongComparisonTest, TestPath) { EXPECT_EQ(song1.get_path(), "Path1"); }
