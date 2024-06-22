#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void list_files(const fs::path& dir, std::vector<std::string>& files, std::vector<bool>& is_directory);
void display_files(const std::vector<std::string>& files, const std::vector<bool>& is_directory, int highlight, const fs::path& current_path, bool tree_mode);
void create_new_file(const fs::path& dir);
void list_files_recursive(const fs::path& dir, std::vector<std::string>& files, std::vector<bool>& is_directory);

#endif // CONTROLLER_H
