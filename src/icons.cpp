#include "icons.h"

std::string get_icon(const fs::path& path){
    if (fs::is_directory(path)){
        return  "📁";
    } else {
        static std::unordered_map<std::string, std::string> extensions_to_icons = {
            {".txt", "📝"},
            {".cpp", "👾"},
            {".h", "🔖"},
            {".md", "📄"},
        };
        auto ext = path.extension().string();
        if (extensions_to_icons.find(ext) != extensions_to_icons.end()){
            return extensions_to_icons[ext];
        } else {
            return "📄";
        }
    }
}
