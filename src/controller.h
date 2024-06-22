#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <ncurses.h>
#include <fstream>

namespace fs = std::filesystem;

void list_files(const fs::path& directory, std::vector<std::string>& files, std::vector<bool>& is_directory);

void list_files_recursive(const fs::path& directory, std::vector<std::string>& files, std::vector<bool>& is_directory, const std::string& prefix);

void display_files(const std::vector<std::string>& files, const std::vector<bool>& is_directory, int highlight, const fs::path& current_path, bool tree_mode);

void create_new_file(const fs::path& current_path);
#endif // CONTROLLER_H
