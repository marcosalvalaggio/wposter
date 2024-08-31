#pragma once
#include <string>
#include <vector>

namespace poster {

    struct Wallpaper {
        std::string path;
        std::string name;
    };

    void saveWallpaper(const Wallpaper& wp);

    std::vector<Wallpaper> loadWallpapers();

    std::string searchWallpaper(const std::string& targetName);

    std::wstring stringToWstring(const std::string& str);

    void stickWallpaper(const std::string& targetName);

    void deleteWallpaper(const std::string& targetName);

    void listWallpapers();

}
