#include <iostream>
#include <fstream>
#include "utils.h"
#include <cstdlib>

namespace utils {

    std::string getPathDB() {
        char* homeDrive = nullptr;
        char* homePath = nullptr;
        size_t len = 0;
        // Retrieve HOMEDRIVE
        _dupenv_s(&homeDrive, &len, "HOMEDRIVE");
        if (homeDrive == nullptr) {
            std::cerr << "Failed to get HOMEDRIVE environment variable" << std::endl;
            return "";
        }
        // Retrieve HOMEPATH
        _dupenv_s(&homePath, &len, "HOMEPATH");
        if (homePath == nullptr) {
            std::cerr << "Failed to get HOMEPATH environment variable" << std::endl;
            free(homeDrive);
            return "";
        }
        // Construct the home directory path
        std::string homePathStr = std::string(homeDrive) + std::string(homePath);
        // std::cout << homePathStr << std::endl;
        // Construct the database path
        std::string dbPath = homePathStr + "\\wposter.csv";
        // std::cout << dbPath << std::endl;
        // Free the memory allocated by _dupenv_s
        free(homeDrive);
        free(homePath);
        return dbPath;
    }

    void checkAndCreateDB() {
        std::string dbPath = getPathDB();
        std::ifstream infile(dbPath);
        if (!infile.good()) {
            std::ofstream outfile(dbPath);
            if (outfile.is_open()) {
                std::cout << "DB created succesfully" << std::endl;
                outfile.close();
            }
            else {
                std::cerr << "Failed to create the wposter DB" << std::endl;
            }
        }
        else {
            // std::cout << "DB wposter already exist" << std::endl;
        }
    }

    void help() {
        std::cout << "Options:" << std::endl;
        std::cout << "  --collect -c <path>, <name> (save wallpaper path)" << std::endl;
        std::cout << "  --stick -s <name> (switch desktop wallpaper to selected name saved)" << std::endl;
        std::cout << "  --delete -d <name> (delete saved desktop wallpaper name)" << std::endl;
        std::cout << "  --list -l (list all wallpaper name)" << std::endl;
    }

}