# Detect operating system
UNAME_S := $(shell uname -s 2>/dev/null || echo "Linux")
OS := $(shell uname -o 2>/dev/null || echo "Unknown")

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib
INCLUDE_DIR = include

# Library target
LIBTARGET = $(BIN_DIR)/sgflib.a

# Source files for the library
LIB_SOURCES = $(SRC_DIR)/entity.cpp \
              $(SRC_DIR)/player.cpp \
              $(SRC_DIR)/enemy.cpp \
              $(SRC_DIR)/collectable.cpp \
              $(SRC_DIR)/world.cpp \
              $(SRC_DIR)/rayAddOn.cpp

# Object files
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
    # Linux settings
    RAYLIB_LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11
    RAYLIB_LIB_PATH = -L$(LIB_DIR)
    LDFLAGS = $(RAYLIB_LIB_PATH) $(RAYLIB_LIBS)
endif

ifeq ($(UNAME_S),Darwin)
    # macOS settings
    RAYLIB_LIBS = -lraylib -framework IOKit -framework Cocoa -framework OpenGL
    RAYLIB_LIB_PATH = -L$(LIB_DIR)
    LDFLAGS = $(RAYLIB_LIB_PATH) $(RAYLIB_LIBS)
    # On macOS, raylib might be installed via Homebrew
    ifeq ($(wildcard /opt/homebrew/lib/libraylib.a),)
        ifeq ($(wildcard /usr/local/lib/libraylib.a),)
            # Try pkg-config if available
            ifneq ($(shell which pkg-config 2>/dev/null),)
                RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
                RAYLIB_LIBS := $(shell pkg-config --libs raylib 2>/dev/null)
                CXXFLAGS += $(RAYLIB_CFLAGS)
                LDFLAGS = $(RAYLIB_LIBS)
            endif
        else
            RAYLIB_LIB_PATH = -L/usr/local/lib
            LDFLAGS = $(RAYLIB_LIB_PATH) $(RAYLIB_LIBS)
        endif
    else
        RAYLIB_LIB_PATH = -L/opt/homebrew/lib
        LDFLAGS = $(RAYLIB_LIB_PATH) $(RAYLIB_LIBS)
    endif
endif

ifeq ($(OS),Msys)
    # Windows (MinGW/MSYS2)
    RAYLIB_LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    RAYLIB_LIB_PATH = -L$(LIB_DIR)
    LDFLAGS = $(RAYLIB_LIB_PATH) $(RAYLIB_LIBS)
    # Windows executable extension
    EXE_EXT = .exe
else
    EXE_EXT =
endif

# Default target
all: directories $(LIBTARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(INCLUDE_DIR)

# Build static library
$(LIBTARGET): $(LIB_OBJECTS)
	@echo "Creating static library: $@"
	ar rcs $@ $^
	@echo "Library created successfully!"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build only the library (for framework users)
onlyLib: directories $(LIBTARGET)

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(LIBTARGET)
	@echo "Clean complete!"

# Deep clean (removes all generated directories)
distclean: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Help target
help:
	@echo "SGF (Simple Game Framework) Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all       - Build the static library (default)"
	@echo "  onlyLib   - Build only the static library"
	@echo "  clean     - Remove object files and library"
	@echo "  distclean - Remove all build directories"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Platform: $(UNAME_S)"
	@echo "Library will be created at: $(LIBTARGET)"

.PHONY: all onlyLib clean distclean help directories
