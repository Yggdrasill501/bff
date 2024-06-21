#include "controller.h"

void list_files(const fs::path& directory, std::vector<std::string>& files, std::vector<bool>& is_directory) {
    files.clear();
    is_directory.clear();
    if (fs::exists(directory) && fs::is_directory(directory)) {
        if (directory.has_parent_path()) {
            files.push_back("..");
            is_directory.push_back(true);
        }
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
    echo();
    mvprintw(LINES - 1, 0, "Enter new file name: ");
    char filename[256];
    getnstr(filename, 255);
    noecho();

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
