#include <iostream>
#include <windows.h>
#include <string>
#include "utils.h"
#include "poster.h"

int main(int argc, char* argv[]) {
    // DB operations
    utils::checkAndCreateDB();
    // cli parsing
    std::string command = argv[1];
    // std::cout << command << std::endl;

    // cli branches
    if (command == "--collect" || command == "-c") { //collect branch
        // std::cout << "num params: " << argc << std::endl;
        if (argc != 4) {
            std::cerr << "wposter argument error: Exactly three arguments are required: (collect, <path>, <name>)" << std::endl;
            return 1;
        }
        // save the wallpaper to the DB
        std::string path = argv[2];
        std::string name = argv[3];
        poster::Wallpaper wp = { path, name };
        poster::saveWallpaper(wp);
    }
    else if (command == "--stick" || command == "-s") { //stick branch
        // std::cout << "num params: " << argc << std::endl;
        if (argc != 3) {
            std::cerr << "wposter argument error: Exactly two arguments are required: (stick, <name>)";
            return 1;
        }
        std::string name = argv[2];
        // call the poster function to set the wallpaper selecetd by name
        poster::stickWallpaper(name);
    }
    else if (command == "--delete" || command == "-d") { //delete branch
        if (argc != 3) {
            std::cerr << "wposter argument error: exactly two arguments are required: (delete <name>)";
            return 1;
        }
        std::string name = argv[2];
        poster::deleteWallpaper(name);
    }
    else if (command == "--list" || command == "-l") { //list branch
        if (argc != 2) {
            std::cerr << "wposter argument error: exactly one argument are required: (list)";
            return 1;
        }
        poster::listWallpapers();
    }
    else if (command == "--help" || command == "-h") { // help branch    utils::help();
        utils::help();
    }
    else if (command == "--version" || command == "-v") {
        std::cout << "wposter 0.0.1" << std::endl;
    }
    else { // error branch
        utils::help();
    }

    return 0;

}