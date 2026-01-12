# Simple-Game-Framework
This is a simple, object oriented and lightweight framework for creating games. It is based upon raylib (the license of which shall is to be found on the bottom of this README), but offers more features that make it even easier to create games. This is my first project, so do not take my word for granted.

## Overview
- This library is suposed to be a superset of the raylib library.
- It's s lightweight Game Engine without a graphical user interface.
- No ECS (Entity Component System) just raw object oriented power.
- Easy to use and flexible.

# Building the project
The Makefile automatically detects the operating system and configures appropriate compiler settings.

## Platform Detection

- **Linux**: Uses g++ with Linux-specific flags
- **macOS**: Uses clang++ with macOS-specific flags  
- **Windows**: Uses g++ with Windows-specific flags (MinGW)

## Directory Structure

```
lib/
├── linux/     # Linux builds
├── macos/     # macOS builds
└── windows/   # Windows builds
```

## Build Targets

- `make all`: Build the library for the detected platform
- `make clean`: Clean build artifacts
- `make help`: Show available targets

The compiled library will be placed in the appropriate platform subdirectory under `lib/`.

# Raylib License
```
Copyright (c) 2013-2026 Ramon Santamaria (@raysan5)

This software is provided "as-is", without any express or implied warranty. In no event 
will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you 
  wrote the original software. If you use this software in a product, an acknowledgment 
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.
```
You should definitly checkout the github repository of raylib. It truly is an amazing library. (https://github.com/raysan5/raylib)
