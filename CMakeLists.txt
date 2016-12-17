cmake_minimum_required(VERSION 3.6)
project(cavestory)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    content/backgrounds/bkBlue.png
    content/sprites/MyChar.png
    content/tilesets/PrtCave.png
    "maps/Map 1.tmx"
    source/headers/AnimatedSprite.h
    source/headers/Game.h
    source/headers/Global.h
    source/headers/Graphics.h
    source/headers/Input.h
    source/headers/Level.h
    source/headers/Player.h
    source/headers/Sprite.h
    source/headers/Tile.h
    source/headers/tinyxml2.h
    source/src/AnimatedSprite.cpp
    source/src/Game.cpp
    source/src/Graphics.cpp
    source/src/Input.cpp
    source/src/Level.cpp
    source/src/main.cpp
    source/src/Player.cpp
    source/src/Sprite.cpp
    source/src/Tile.cpp
    source/src/tinyxml2.cpp
    README.md)

add_executable(cavestory ${SOURCE_FILES})