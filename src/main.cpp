#include <filesystem>
#include <vector>
#include <string>
#include <ncurses.h>
#include "controller.h"

namespace fs = std::filesystem;

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

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

    endwin();
    return 0;
}
