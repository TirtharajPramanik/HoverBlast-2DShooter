#pragma once
#include <raylib.h>

const char windowTitle[] = "Hover Blast";
const int windowWidth = 900, windowHeight = 800, statsWidth = 100;
const int frameRate = 60, maxShipSpeed = 500, maxShotSpeed = 600, maxShots = 12;
const int bgSpan = 300, xGameOffset = bgSpan, yGameOffset = bgSpan, xMenuOffset = bgSpan, yMenuOffset = bgSpan;

int arenaWidth(void) { return GetScreenWidth(); }
int arenaHeight(void) { return GetScreenHeight() / 2; }

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

void drawStats(char *name, int score, int health, int yPos, int fontSize, Color color)
{
    DrawText(name, fontSize, yPos, fontSize, color);
    DrawText(TextFormat("Score %d", score), fontSize, yPos + fontSize, fontSize, color);
    DrawText(TextFormat("Health %d", health), fontSize, yPos + fontSize * 2, fontSize, color);
}

// #define DEBUG