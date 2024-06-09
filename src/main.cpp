#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <ncurses.h>

namespace fs = std::filesystem;

void list_files(const fs::path& directory, std::vector<std::string>& files) {
    files.clear();
    if (fs::exists(directory) && fs::is_directory(directory)) {
        for (const auto& entry : fs::directory_iterator(directory)) {
            files.push_back(entry.path().filename().string());
        }
    }
}

void display_files(const std::vector<std::string>& files, int highlight) {
    clear();
    for (size_t i = 0; i < files.size(); ++i) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i, 0, files[i].c_str());
        if (i == highlight) {
            attroff(A_REVERSE);
        }
    }
    refresh();
}

int main() {
    initscr();            // Start curses mode
    cbreak();             // Line buffering disabled
    noecho();             // Don't echo while we do getch
    keypad(stdscr, TRUE); // Enable function keys and arrow keys

    fs::path current_path = fs::current_path();
    std::vector<std::string> files;
    int highlight = 0;

    list_files(current_path, files);
    display_files(files, highlight);

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
        case KEY_UP:
            if (highlight > 0) {
                highlight--;
            }
            break;
        case KEY_DOWN:
            if (highlight < files.size() - 1) {
                highlight++;
            }
            break;
        case 10: // Enter key
            if (fs::is_directory(current_path / files[highlight])) {
                current_path /= files[highlight];
                list_files(current_path, files);
                highlight = 0;
            }
            break;
        }
        display_files(files, highlight);
    }

    endwin(); // End curses mode
    return 0;
}
