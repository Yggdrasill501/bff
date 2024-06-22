#include "controller.h"
#include <ncurses.h>
#include <fstream>

void list_files(const fs::path& dir, std::vector<std::string>& files, std::vector<bool>& is_directory) {
    files.clear();
    is_directory.clear();

    if (dir.has_parent_path()) {
        files.push_back("..");
        is_directory.push_back(true);
    }

    for (const auto& entry : fs::directory_iterator(dir)) {
        files.push_back(entry.path().filename().string());
        is_directory.push_back(entry.is_directory());
    }
}

void list_files_recursive(const fs::path& dir, std::vector<std::string>& files, std::vector<bool>& is_directory, const std::string& prefix = "") {
    files.clear();
    is_directory.clear();

    if (dir.has_parent_path()) {
        files.push_back(prefix + "..");
        is_directory.push_back(true);
    }

    for (const auto& entry : fs::directory_iterator(dir)) {
        files.push_back(prefix + entry.path().filename().string());
        is_directory.push_back(entry.is_directory());

        if (entry.is_directory()) {
            list_files_recursive(entry.path(), files, is_directory, prefix + "    ");
        }
    }
}

void display_files(const std::vector<std::string>& files, const std::vector<bool>& is_directory, int highlight, const fs::path& current_path, bool tree_mode) {
    clear();
    mvprintw(0, 0, current_path.c_str());
    for (int i = 0; i < files.size(); i++) {
        if (i == highlight) {
            wattron(stdscr, A_REVERSE);
        }
        mvprintw(i + 2, 0, files[i].c_str());
        wattroff(stdscr, A_REVERSE);
    }
    refresh();
}

void create_new_file(const fs::path& dir) {
    echo();
    mvprintw(LINES - 1, 0, "Enter new file name: ");
    char file_name[256];
    getstr(file_name);
    noecho();

    fs::path new_file_path = dir / file_name;
    std::ofstream new_file(new_file_path.string());
}
