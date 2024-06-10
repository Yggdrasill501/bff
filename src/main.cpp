#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <ncurses.h>
#include <fstream>

namespace fs = std::filesystem;

void list_files(const fs::path& directory, std::vector<std::string>& files, std::vector<bool>& is_directory) {
    files.clear();
    is_directory.clear();
    if (fs::exists(directory) && fs::is_directory(directory)) {
        for (const auto& entry : fs::directory_iterator(directory)) {
            files.push_back(entry.path().filename().string());
            is_directory.push_back(entry.is_directory());
        }
    }
}

void display_files(const std::vector<std::string>& files, const std::vector<bool>& is_directory, int highlight) {
    clear();
    for (size_t i = 0; i < files.size(); ++i) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        std::string display_name = is_directory[i] ? "[D] " : "- ";
        display_name += files[i];
        mvprintw(i, 0, display_name.c_str());
        if (i == highlight) {
            attroff(A_REVERSE);
        }
    }
    refresh();
}

void create_new_file(const fs::path& current_path) {
    echo();  // Enable echoing of characters
    mvprintw(LINES - 1, 0, "Enter new file name: ");
    char filename[256];
    getnstr(filename, 255);
    noecho();  // Disable echoing of characters again

    fs::path new_file_path = current_path / filename;
    std::ofstream new_file(new_file_path.string());
    if (new_file) {
        new_file.close();
        mvprintw(LINES - 1, 0, "File created successfully.           ");
    } else {
        mvprintw(LINES - 1, 0, "Failed to create file.              ");
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
    std::vector<bool> is_directory;
    int highlight = 0;

    list_files(current_path, files, is_directory);
    display_files(files, is_directory, highlight);

    int ch;
    while (true) {
        ch = getch();
        if (ch == 'q') {
            break;
        } else if (ch == '%') {
            create_new_file(current_path);
            list_files(current_path, files, is_directory);
            highlight = 0;
        } else {
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
                if (is_directory[highlight]) {
                    current_path /= files[highlight];
                    list_files(current_path, files, is_directory);
                    highlight = 0;
                }
                break;
            }
        }
        display_files(files, is_directory, highlight);
    }

    endwin(); // End curses mode
    return 0;
}
