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

void list_files_recursive(const fs::path& directory, std::vector<std::string>& files, std::vector<bool>& is_directory, const std::string& prefix = "") {
    if (fs::exists(directory) && fs::is_directory(directory)) {
        std::string new_prefix;
        for (const auto& entry : fs::directory_iterator(directory)) {
            new_prefix = prefix + "├── ";
            if (entry.is_directory()) {
                files.push_back(prefix + "└── " + entry.path().filename().string() + "/");
                is_directory.push_back(true);
                list_files_recursive(entry, files, is_directory, new_prefix + "    ");
            } else {
                files.push_back(new_prefix + entry.path().filename().string());
                is_directory.push_back(false);
            }
        }
    }
}

void display_files(const std::vector<std::string>& files, const std::vector<bool>& is_directory, int highlight, const fs::path& current_path, bool tree_mode) {
    clear();
    mvprintw(0, 0, "Current Path: %s", current_path.c_str());
    mvprintw(1, 0, "Mode: %s", tree_mode ? "Tree" : "List");

    for (size_t i = 0; i < files.size(); ++i) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i + 2, 0, files[i].c_str());
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
}
