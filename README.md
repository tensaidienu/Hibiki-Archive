# Hibiki Game Engine

## Hibiki - ALPHA Version

### Hibiki the best open source 2D game engine made with SDL in C++.

---
***
---



## Links

***

The Hibiki web site . . . . . . . . .

Support . . . . . . . . . . . . . . . . . .

Forums  . . . . . . . . . . . . . . . . . .

Wiki  . . . . . . . . . . . . . . . . . . . . .

## Source Code Content

***

AUTHORS            - Hibiki authors.

LICENSE            - The MIT license.

NEWS               - Important modifications between the releases.

README             - This file.

THANKS             - Hibiki contributors.


Assets/            - Assets files folder.

Build/             - Build files folder.

Source/            - Source files folder.

WebSource/         - Web Source files folder.


## Build Instructions

### Prerequisites

##### Programs
- [Git](https://git-scm.com) -> Source control
- [CMake](https://cmake.org) -> Configure the project build
- [Make](https://www.gnu.org/software/make) -> Build the project using the configuration saved
- [GCC](https://gcc.gnu.org) -> To build for Linux
- [MinGW](http://www.mingw.org) -> To build for Windows
- [Emscripten](https://emscripten.org) -> To build for Web

##### Libraries
*You need to install the library for the compile you will use GCC or MinGW, if you will be using the two you need to install the libraries for the two compilers.

- [SDL2](https://www.libsdl.org/download-2.0.php) -> SDL2 Library
- [SDL2 TTF](https://www.libsdl.org/projects/SDL_ttf) -> SDL2 TTF Module
- [SDL2 Mixer](https://www.libsdl.org/projects/SDL_mixer) -> SDL2 Mixer Module
- [SDL2 Image](https://www.libsdl.org/projects/SDL_image) -> SDL2 Image Module
- [SDL2 NET](https://www.libsdl.org/projects/SDL_net) -> SDL2 NET Module
- [SDL2 GFX](https://sourceforge.net/projects/sdl2gfx) -> SDL2 GFX Module
- [zlib](https://www.zlib.net) -> zlib library

### Build

##### -PC Version-
- Use CMake and set the Build and Source Folders then click in generate and configure.

- Using the console go to the build folder and use the 'make' command, the build files will be placed inside the Build folder.

##### -Web Version-
- Using the console go to the source folder and then use one of the commands in the EMSCRIPTEN.txt file, the build files will be placed inside WebBuild folder, the web version only works on a web server.

## License
Copyright (c) 天才ディエヌ - (TensaiDN). All rights reserved.

Licensed under the MIT license.