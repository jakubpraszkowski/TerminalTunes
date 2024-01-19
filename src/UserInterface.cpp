#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::entryPoint() {
    FileManager fm;
    fm.scanDirectory();
    MusicLibrary ml;
    ml.updateSongs(fm);
    UserInterface ui;
    AudioPlayer ap;
    ui.drawWindowsOnScreen(ml, ap);
}

void UserInterface::drawWindowsOnScreen(MusicLibrary &ml, AudioPlayer &ap) {
    int ch;
    initNcurses();
    std::thread playbackThread;
    WINDOW_INIT winInit;
    WIN_BOX winBox;

    do {
        getmaxyx(stdscr, winInit.mainWinHeight, winInit.mainWinWidth);

        WINDOW *sidebarWin = newwin(
            winInit.mainWinHeight, winInit.sidebarWinWidth, winInit.sidebarWinY,
            winInit.sidebarWinX);
        WINDOW *topWin = newwin(
            winInit.topWinHeight,
            winInit.mainWinWidth - winInit.sidebarWinWidth, winInit.topWinY,
            winInit.sidebarWinWidth);
        WINDOW *mainWin = newwin(
            winInit.mainWinHeight - winInit.topWinHeight,
            winInit.mainWinWidth - winInit.sidebarWinWidth,
            winInit.topWinHeight, winInit.sidebarWinWidth);

        box(sidebarWin, 0, 0);
        box(topWin, 0, 0);
        box(mainWin, 0, 0);

        moveOnScreenWithKeys(
            ml, ap, winBox, ch, playbackThread, mainWin, topWin, sidebarWin);

        printCurrentSong(ap, topWin);

        wrefresh(sidebarWin);
        wrefresh(topWin);
        wrefresh(mainWin);

    } while ((ch = getch()) != KEY_F(1));

    if (playbackThread.joinable())
        playbackThread.join();

    endwin();
    delwin(stdscr);
}

void UserInterface::moveOnScreenWithKeys(
    MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
    std::thread &playbackThread, WINDOW *mainWin, WINDOW *topWin,
    WINDOW *sidebarWin) {
    switch (ch) {
    case '\t':
        winBox.currentBox = (winBox.currentBox % 2) + 1;
        break;

    case KEY_UP:
        processKeyUp(winBox);
        break;

    case KEY_DOWN:
        processKeyDown(winBox, ml);
        break;

    case KEY_F(4):
        if (winBox.currentBox == 1) {
            leftMenuAction(winBox, ml, ap);
        } else if (winBox.currentBox == 2 && winBox.currentLine1stBox == 0) {
            if (!playbackThread.joinable()) {
                playbackThread = std::thread([&ap]() { ap.playQueue(); });
            }
        }
        break;

    case KEY_RIGHT:
        if (ap.checkMusicPlaying()) {
            ap.advanceForwardMusic(ap.getCurrentMusic());
        }
        break;

    case KEY_LEFT:
        if (ap.checkMusicPlaying()) {
            ap.advanceBackwardMusic(ap.getCurrentMusic());
        }
        break;

    case char('s'):
        if (ap.checkMusicPlaying()) {
            ap.stopMusic(ap.getCurrentMusic());
        }
        break;

    case char('p'):
        ap.pauseOrResumeMusic(ap.getCurrentMusic());
        break;

    default:
        break;
    }

    MENU_BOOL menuBool;
    whichVectorShow(winBox, menuBool, ml, mainWin, topWin);
}

template <typename T>
void UserInterface::printVectorInsideWindow(
    MusicLibrary &ml, WINDOW *mainWin, int &currentLine, std::vector<T> &vec) {
    if (vec.empty()) {
        if (typeid(T) == typeid(Playlist)) {
            noPlaylists(mainWin);
        }
        return;
    }

    int maxLines = mainWin->_maxy - 2;

    if (currentLine < 0)
        currentLine = 0;
    if (currentLine >= vec.size())
        currentLine = vec.size() - 1;

    int startIdx = currentLine;
    int endIdx =
        std::min(currentLine + maxLines, static_cast<int>(vec.size()) - 1);

    for (int i = startIdx; i <= endIdx; i++) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                vec[i].getTitle().c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                vec[i].getTitle().c_str());
        }
    }
}

void UserInterface::printVectorInsideWindow(
    MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
    std::vector<std::shared_ptr<Song>> &vec) {
    int maxLines = mainWin->_maxy - 2;

    if (currentLine < 0)
        currentLine = 0;
    if (currentLine >= vec.size())
        currentLine = vec.size() - 1;

    int startIdx = currentLine;
    int endIdx =
        std::min(currentLine + maxLines, static_cast<int>(vec.size()) - 1);

    for (int i = startIdx; i <= endIdx; i++) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                (*vec[i]).getTitle().c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                (*vec[i]).getTitle().c_str());
        }
    }
}

template <typename T>
void UserInterface::moveDown(std::vector<T> &vec, int &currentLine) {
    if (currentLine < vec.size() - 1) {
        currentLine++;
    }
}

void UserInterface::moveUp(int &currentLine) {
    if (currentLine > 0) {
        currentLine--;
    }
}

void UserInterface::moveDown(
    int &currentLine, std::function<int()> getSizeFunc) {
    if (currentLine < getSizeFunc() - 1) {
        currentLine++;
    }
}

template <typename T>
void UserInterface::printMenu(
    int &currentLine, std::function<std::string(T)> getMenuOptionFunc) {
    for (int i = 0; i < static_cast<int>(T::MENU_SIZE); i++) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(
                1 + i, 1, "%s", getMenuOptionFunc(static_cast<T>(i)).c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                1 + i, 1, "%s", getMenuOptionFunc(static_cast<T>(i)).c_str());
        }
    }
}

void UserInterface::printStatus(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.isDequeEmpty()) {
        mvprintw(
            topWin->_begy + 1, topWin->_begx + 10, "%s",
            musicStatus[2].c_str());
    } else if (ap.checkMusicPlaying()) {
        mvprintw(1, 1, "%s", musicStatus[0].c_str());
    } else {
        mvprintw(1, 1, "%s", musicStatus[1].c_str());
    }
}

void UserInterface::printProgressBar(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.checkMusicPlaying()) {
        float progressBar = ap.calculateSongProgressBar(ap.getCurrentMusic());
        int progressBarLength = static_cast<int>(progressBar * 100);

        mvwprintw(topWin, topWin->_begy + 1, topWin->_begx + 11, "[");
        wattron(topWin, A_REVERSE);
        for (int i = 0; i < progressBarLength; ++i) {
            wprintw(topWin, "=");
        }
        wattroff(topWin, A_REVERSE);
        for (int i = progressBarLength; i < 20; ++i) {
            wprintw(topWin, " ");
        }
        wprintw(topWin, "]");

        wrefresh(topWin);
    }
}

void UserInterface::printCurrentSong(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.checkMusicPlaying()) {
        mvprintw(
            topWin->_begy + 1, topWin->_begx + 10, "%s",
            ap.getSongQueueFront()->getTitle().c_str());
    }
}

void UserInterface::initNcurses() {
    initscr();
    refresh();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}

void UserInterface::processKeyUp(WIN_BOX &winBox) {
    if (winBox.currentBox == 1) {
        moveUp(winBox.currentLine3rdBox);
    } else if (winBox.currentBox == 2) {
        moveUp(winBox.currentLine1stBox);
    }
}

void UserInterface::processKeyDown(WIN_BOX &winBox, MusicLibrary &ml) {
    if (winBox.currentBox == 1) {
        moveDown(ml.getSongs(), winBox.currentLine3rdBox);
    } else if (winBox.currentBox == 2) {
        moveDown(winBox.currentLine1stBox, []() {
            return static_cast<int>(MENU::MENU_SIZE);
        });
    }
}

void UserInterface::leftMenuAction(
    WIN_BOX &winBox, MusicLibrary &ml, AudioPlayer &ap) {
    if (winBox.currentLine1stBox == static_cast<int>(MENU::SONGS)) {
        ap.loadSound2Queue(winBox.currentLine3rdBox, ml.getSongs());
    } else if (winBox.currentLine1stBox == static_cast<int>(MENU::ALBUMS)) {
        ap.loadSound2Queue(winBox.currentLine3rdBox, ml.getAlbums());
    } else if (winBox.currentLine1stBox == static_cast<int>(MENU::SHUFFLE)) {
        ap.shuffleQueue();
    } else if (winBox.currentLine1stBox == static_cast<int>(MENU::PLAYLISTS)) {
    }
}

void UserInterface::whichVectorShow(
    WIN_BOX &winBox, MENU_BOOL &menuBool, MusicLibrary &ml, WINDOW *mainWin,
    WINDOW *topWin) {
    if (winBox.currentLine1stBox == static_cast<int>(MENU::SONGS)) {
        menuBool.isSongMenu = true;
        menuBool.isAlbumMenu = false;
        menuBool.isPlaylistMenu = false;

    } else if (winBox.currentLine1stBox == static_cast<int>(MENU::ALBUMS)) {
        menuBool.isSongMenu = false;
        menuBool.isAlbumMenu = true;
        menuBool.isPlaylistMenu = false;

    } else if (winBox.currentLine1stBox == static_cast<int>(MENU::PLAYLISTS)) {
        menuBool.isSongMenu = false;
        menuBool.isAlbumMenu = false;
        menuBool.isPlaylistMenu = true;
    }

    if (menuBool.isSongMenu && !menuBool.isAlbumMenu &&
        !menuBool.isPlaylistMenu) {

        printVectorInsideWindow(
            ml, mainWin, winBox.currentLine3rdBox, ml.getSongs());
    } else if (
        menuBool.isAlbumMenu && !menuBool.isSongMenu &&
        !menuBool.isPlaylistMenu) {
        printVectorInsideWindow(
            ml, mainWin, winBox.currentLine3rdBox, ml.getAlbums());
    } else if (
        !menuBool.isAlbumMenu && !menuBool.isSongMenu &&
        menuBool.isPlaylistMenu) {
        printVectorInsideWindow(
            ml, mainWin, winBox.currentLine3rdBox, ml.getPlaylists());
    }

    printMenu<MENU>(winBox.currentLine1stBox, [this](MENU menu) {
        return this->getMenuOption(menu);
    });
}

void UserInterface::updateUI(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.checkMusicPlaying()) {
        while (true) {
            printProgressBar(ap, topWin);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void UserInterface::statusThread(AudioPlayer &ap, WINDOW *topWin) {
    std::thread uiThread(&UserInterface::updateUI, this, std::ref(ap), topWin);
    uiThread.detach();
}

void UserInterface::createPlaylistMenu(
    WINDOW *topWin, int &ch, MusicLibrary &ml, WINDOW *mainWin) {
    wrefresh(mainWin);
    mvprintw(
        topWin->_begy + 1, topWin->_begx + 10, "%s", "Playlist Creation Mode");
    mvprintw(
        topWin->_begy + 3, topWin->_begx + 10, "%s", "Enter playlist name: ");
    std::string input;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE && !input.empty()) {
            input.pop_back();
            mvprintw(topWin->_begy + 3, topWin->_begx + 30, "");
        } else if (isprint(ch)) {
            input.push_back(ch);
        };
        mvprintw(topWin->_begy + 3, topWin->_begx + 30, "%s", input.c_str());
    }
    Playlist newPlaylist(input);
    ml.addPlaylist(newPlaylist);
    wrefresh(topWin);
}

std::string UserInterface::getMenuOption(MENU menu) {
    switch (menu) {
    case MENU::PLAY:
        return "Play";
    case MENU::SONGS:
        return "Songs";
    case MENU::ALBUMS:
        return "Albums";
    case MENU::SHUFFLE:
        return "Shuffle";
    case MENU::PLAYLISTS:
        return "Playlists";
    default:
        return "UNKNOWN";
    }
}

std::string UserInterface::getPlaylistMenuOption(PLAYLIST_MENU plMenu) {
    switch (plMenu) {
    case PLAYLIST_MENU::ADD_SONG:
        return "Add song";
    case PLAYLIST_MENU::CREATE:
        return "Create";
    case PLAYLIST_MENU::DELETE:
        return "Delete";
    case PLAYLIST_MENU::SHOW:
        return "Show";
    case PLAYLIST_MENU::REMOVE_SONG:
        return "Remove song";
    case PLAYLIST_MENU::GO_BACK:
        return "Go back";
    default:
        return "UNKNOWN";
    }
}

void UserInterface::noPlaylists(WINDOW *mainWin) {
    mvprintw(
        mainWin->_begy + 1, mainWin->_begx + 1, "%s",
        "No playlists created yet");
}

void UserInterface::playlistMenu(
    WINDOW *sidebarWin, int &ch, MusicLibrary &ml, WINDOW *mainWin) {
    wrefresh(sidebarWin);
    wrefresh(mainWin);
}
