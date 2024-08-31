#include <iostream>
#include "poster.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <codecvt>

namespace poster {

    void saveWallpaper(const Wallpaper& wp) {\
        std::string dbPath = utils::getPathDB();
        std::ofstream file(dbPath, std::ios::app); // open in append mode
        if (file.is_open()) {
            file << wp.path << ";" << wp.name << "\n";
            file.close();
            std::cout << "Wallpaper data saved to wposter DB" << std::endl;
        }
        else {
            std::cerr << "Unable to open file for writing wallpaper" << std::endl;
        }
    }

    std::vector<Wallpaper> loadWallpapers() {
        std::string dbPath = utils::getPathDB();
        std::vector<Wallpaper> wallpapers;
        std::ifstream file(dbPath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string path, name;
                // split the line into path and name
                std::getline(ss, path, ';');
                std::getline(ss, name);
                // create a Wallpaper instance and add to the vector
                wallpapers.push_back(Wallpaper{ path, name });
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open wposter DB" << std::endl;
        }
        return wallpapers;
    }

    std::string searchWallpaper(const std::string& targetName) {
        std::vector<Wallpaper> wallpapers = loadWallpapers();
        for (const auto& wp : wallpapers) {
            std::string path = wp.path;
            std::string name = wp.name;
            if (name == targetName) {
                std::cout << "Wallpaper match: " << name << std::endl;
                return path;
            }
        }
        // If no match is found, return an empty string or a specific error value
        std::cerr << "Unable to find wallpaper: " << targetName << std::endl;
        return "";
    }

    std::wstring stringToWstring(const std::string& str) {
        // Create a wstring_convert object
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        // Convert the string
        return converter.from_bytes(str);
    }

    void stickWallpaper(const std::string& targetName) {
        std::string path = searchWallpaper(targetName);
        if (path == "") {
            return;
        }
        std::cout << path << std::endl;
        std::wstring pathWstr = stringToWstring(path);
        const wchar_t* targetPath = pathWstr.c_str();
        std::wcout << "target path: " << targetPath << std::endl;
        const wchar_t* testPath = L"C:\\Users\\marsa\\Documents\\wallpaper\\lana.png";
        std::wcout << "test path: " << testPath << std::endl;
        // pathWstr.c_str() to get const wchar_t*
        int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)targetPath, SPIF_UPDATEINIFILE);
        std::cout << "Result: " << result << std::endl;
    }

    void deleteWallpaper(const std::string& targetName) {
        std::string dbPath = utils::getPathDB();
        std::ifstream inputFile(dbPath);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening wposter DB for reading" << std::endl;
            return;
        }
        std::ofstream tempFile("wposter_temp.csv");
        if (!tempFile.is_open()) {
            std::cerr << "Error opening wposter temp DB for writing" << std::endl;
            return;
        }
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string path, name;
            // split the line into path and name
            std::getline(ss, path, ';');
            std::getline(ss, name);
            if (name != targetName) {
                tempFile << line << std::endl;
            }
            else {
                std::cout << "Removed wallpaper: " << name << " " << path << std::endl;
            }
        }
        inputFile.close();
        tempFile.close();
        // delete wposter and rename wposter_temp to wposter
        if (std::remove(dbPath.c_str()) != 0) {
            std::cerr << "Error deleting wposter DB" << std::endl;
            return;
        }
        // rename
        if (std::rename("wposter_temp.csv", dbPath.c_str()) != 0) {
            std::cerr << "Error renaming wposter_temp DB file" << std::endl;
            return;
        }
    }

    void listWallpapers() {
        std::cout << "wposter wallpapers list:" << std::endl;
        std::string dbPath = utils::getPathDB();
        std::ifstream file(dbPath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string path, name;
                // split the line into path and name
                std::getline(ss, path, ';');
                std::getline(ss, name);
                std::cout << "(*) "  << name << " " << path << std::endl;
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open wposter DB" << std::endl;
        }
        std::cout << std::endl;
    }

}