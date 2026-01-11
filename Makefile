# Detect operating system
UNAME_S := $(shell uname -s 2>/dev/null || echo "Linux")
ifeq ($(OS),Windows_NT)
    DETECTED_OS = Windows
else
    DETECTED_OS := $(shell uname -s 2>/dev/null || echo "Linux")
endif

# Compiler settings based on OS
ifeq ($(DETECTED_OS),Windows)
    CXX = g++
    CXXFLAGS = -std=c++23 -Wall -Wextra -Iinclude -DWIN32
    AR = ar
    ARFLAGS = rcs
    LIB_EXT = .a
    RM = del /Q /S 2>nul || rmdir /S /Q
    MKDIR = mkdir
    LIB_SUBDIR = windows
else ifeq ($(DETECTED_OS),Darwin)
    CXX = clang++
    CXXFLAGS = -std=c++23 -Wall -Wextra -Iinclude -D__APPLE__
    AR = ar
    ARFLAGS = rcs
    LIB_EXT = .a
    RM = rm -rf
    MKDIR = mkdir -p
    LIB_SUBDIR = macos
else
    CXX = g++
    CXXFLAGS = -std=c++23 -Wall -Wextra -Iinclude -D__LINUX__
    AR = ar
    ARFLAGS = rcs
    LIB_EXT = .a
    RM = rm -rf
    MKDIR = mkdir -p
    LIB_SUBDIR = linux
endif

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib
INCLUDE_DIR = include

# Platform-specific library directory
PLATFORM_LIB_DIR = $(LIB_DIR)/$(LIB_SUBDIR)

# Library target
LIBTARGET = $(PLATFORM_LIB_DIR)/sgflib$(LIB_EXT)

# Source files for the library
LIB_SOURCES = $(SRC_DIR)/core.cpp
OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
.PHONY: all clean help install

all: $(PLATFORM_LIB_DIR) $(OBJ_DIR) $(LIBTARGET)

# Create directories
$(PLATFORM_LIB_DIR):
	$(MKDIR) $(PLATFORM_LIB_DIR)

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build static library
$(LIBTARGET): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

# Clean build artifacts
clean:
	$(RM) $(OBJ_DIR) $(BIN_DIR)

# Install library (optional)
install: $(LIBTARGET)
	@echo "Library installed to: $(LIBTARGET)"

# Show help
help:
	@echo "SGF Library Build System"
	@echo "========================="
	@echo "Available targets:"
	@echo "  all      - Build the library for detected platform ($(LIB_SUBDIR))"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install library to platform directory"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Detected OS: $(DETECTED_OS)"
	@echo "Library target: $(LIBTARGET)"
