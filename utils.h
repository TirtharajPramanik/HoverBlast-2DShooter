#pragma once
#include <raylib.h>

const char windowTitle[] = "Dungeon Fighter";
const int windowWidth = 800, windowHeight = 800;
const int window_xCellCount = 16, window_yCellCount = 16;
const int gameWidth = windowWidth, gameHeight = windowHeight / 2;
const int game_xCellCount = window_xCellCount, game_yCellCount = window_yCellCount / 2;
const float cellWidth = windowWidth / window_xCellCount, cellHeight = windowHeight / window_yCellCount;
