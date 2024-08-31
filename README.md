## WPOSTER

The *wposter* CLI started as a weekend project before returning to work. What I needed was a CLI tool that allows me to change the wallpaper on my Windows machine. I wanted a way to visually separate my development environment from my work environment. During work hours, I usually collaborate with colleagues, and I prefer not to display my personal setup for after-hours development.

### Build from Source
The project is built and developed using Visual Studio, which works well for invoking the Windows API.

### Usage
The wposter CLI is extremely simple. It provides four main commands:

* **collect**: Save the path of an image you want to use as a desktop wallpaper and give the path a "shortcut" name ```wposter --collect C:\Users\marsa\Documents\wallpaper\lana.png lana```
* **stick**: Switch the desktop wallpaper by calling it by its shortcut name ```wposter --stick lana```
* **delete**: Delete a desktop wallpaper shortcut by its name ```wposter --delete lana```
* **list**: List all the desktop wallpaper shortcuts by their names ```wposter --list```
