#pragma once
#include <raylib.h>

const char windowTitle[] = "Hover Blast";
const int windowWidth = 800, windowHeight = 800;
const int frameRate = 60, maxShipSpeed = 500, maxShotSpeed = 600, maxShots = 12;
const int bgSpan = 300, xGameOffset = bgSpan, yGameOffset = bgSpan, xMenuOffset = bgSpan, yMenuOffset = bgSpan;

int gameWidth(void) { return GetScreenWidth(); }
int gameHeight(void) { return GetScreenHeight(); }
int arenaHeight(void) { return gameHeight() / 2; }

Sound shootSound, blastSound;
Texture2D shotsTexture, shipTexture,
    shipBlastTexture, backgroundTexture;

void loadAssets(void)
{
    shipTexture = LoadTexture("assets/Ship.png");
    shotsTexture = LoadTexture("assets/Shots.png");
    shipBlastTexture = LoadTexture("assets/ShipBlast.png");
    backgroundTexture = LoadTexture("assets/Background.png");

    shootSound = LoadSound("assets/Shoot.wav");
    blastSound = LoadSound("assets/ShipBlast.wav");
}

void unloadAssets(void)
{
    UnloadSound(shootSound);
    UnloadSound(blastSound);

    UnloadTexture(backgroundTexture);
    UnloadTexture(shipBlastTexture);
    UnloadTexture(shotsTexture);
    UnloadTexture(shipTexture);
}

#define DEBUG