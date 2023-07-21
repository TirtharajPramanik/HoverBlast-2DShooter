#pragma once
#include <raylib.h>

const char windowTitle[] = "Hover Blast";
const int windowWidth = 800, windowHeight = 800;
const int frameRate = 60, maxShipSpeed = 500, maxShotSpeed = 600, maxShots = 12;

int gameWidth(void) { return GetScreenWidth(); }
int gameHeight(void) { return GetScreenHeight() / 2; }

#define DEBUG