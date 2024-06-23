#ifndef ICONS_H
#define ICONS_H

#include <string>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

std::string get_icon(const fs::path& path);

#endif //ICONS_H
