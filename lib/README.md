# SGF Library Cross-Platform Build

This Makefile supports building the SGF library on Linux, macOS, and Windows.

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
