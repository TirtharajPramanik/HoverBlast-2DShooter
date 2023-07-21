#pragma once
#include <raylib.h>

const char windowTitle[] = "Hover Blast";
const int windowWidth = 800, windowHeight = 800;
const int frameRate = 60, maxShipSpeed = 500, maxShotSpeed = 600, maxShots = 12;
const int bgSpan = 240, xGameOffset = 0, yGameOffset = bgSpan, xMenuOffset = bgSpan, yMenuOffset = bgSpan;

int gameWidth(void) { return GetScreenWidth(); }
int gameHeight(void) { return GetScreenHeight(); }
int arenaHeight(void) { return gameHeight() / 2; }

// #define DEBUG