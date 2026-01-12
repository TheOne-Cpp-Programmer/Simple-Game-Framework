# Simple-Game-Framework
This is a simple, object oriented and lightweight framework for creating games. It is based upon raylib, but offers more features that make it even easier to create games. This is my first project, so do not take my word for granted.

## Overview
- This library is suposed to be a superset of the raylib library.
- It's s lightweight Game Engine without a graphical user interface.
- No ECS (Entity Component System) just raw object oriented power.
- Easy to use and flexible.

## Building the project

## Platform Detection

The Makefile automatically detects the operating system and configures appropriate compiler settings:

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
