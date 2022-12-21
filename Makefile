SRC_DIR = src
BUILD_DIR = build
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = spacebattle
INCLUDE_PATHS = -Isrc/include
LIBRARY_PATHS = -Lsrc/lib
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(LINKER_FLAGS)
	./build/spacebattle

# g++ -Wall -Isrc/include -Lsrc/lib src/draw.cpp src/game.cpp src/main.cpp src/mechanics.cpp src/spaceobjects.cpp src/stars.cpp -o build/spacebattle -lmingw32 -lSDL2main -lSDL2