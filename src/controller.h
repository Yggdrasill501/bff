#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <filesystem>
#include "fstream"
#include <vector>
#include <string>
#include <ncurses.h>

namespace fs = std::filesystem;

void create_new_file(const fs::path& current_path);

void list_files(const fs::path& directory, std::vector<std::string>& files, std::vector<bool>& is_directory);

void display_files(const std::vector<std::string>& files, const std::vector<bool>& is_directory, int highlight);

#endif // CONTROLLER_H
