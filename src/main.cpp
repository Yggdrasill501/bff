#include <ncurses.h>
#include "controller.h"
#include "icons.h"

int main() {
    initscr();            // Start curses mode
    cbreak();             // Line buffering disabled
    noecho();             // Don't echo while we do getch
    keypad(stdscr, TRUE); // Enable function keys and arrow keys

    fs::path current_path = fs::current_path();
    std::vector<std::string> files;
    std::vector<bool> is_directory;
    int highlight = 0;
    bool tree_mode = false;

    list_files(current_path, files, is_directory);
    display_files(files, is_directory, highlight, current_path, tree_mode);

    int ch;
    while (true) {
        ch = getch();
        if (ch == 'q') {
            break;
        } else if (ch == 't') {
            tree_mode = !tree_mode;
            if (tree_mode) {
                list_files_recursive(current_path, files, is_directory, "");
            } else {
                list_files(current_path, files, is_directory);
            }
            highlight = 0;
        } else if (ch == '%') {
            create_new_file(current_path);
            if (tree_mode) {
                list_files_recursive(current_path, files, is_directory, "");
            } else {
                list_files(current_path, files, is_directory);
            }
            highlight = 0;
        } else {
            switch (ch) {
            case KEY_UP:
            case 'k':
                if (highlight > 0) {
                    highlight--;
                }
                break;
            case KEY_DOWN:
            case 'j':
                if (highlight < files.size() - 1) {
                    highlight++;
                }
                break;
            case 'h':
                if (current_path.has_parent_path()) {
                    current_path = current_path.parent_path();
                    if (tree_mode) {
                        list_files_recursive(current_path, files, is_directory, "");
                    } else {
                        list_files(current_path, files, is_directory);
                    }
                    highlight = 0;
                }
                break;
            case 'l':
            case 10: // Enter key
                if (is_directory[highlight]) {
                    if (files[highlight] == "..") {
                        current_path = current_path.parent_path();
                    } else {
                        current_path /= files[highlight].substr(files[highlight].find_last_of(" ") + 1); // extract actual dir name
                    }
                    if (tree_mode) {
                        list_files_recursive(current_path, files, is_directory, "");
                    } else {
                        list_files(current_path, files, is_directory);
                    }
                    highlight = 0;
                }
                break;
            }
        }
        display_files(files, is_directory, highlight, current_path, tree_mode);
    }

    endwin(); // End curses mode
    return 0;
}
