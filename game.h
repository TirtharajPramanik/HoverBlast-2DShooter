#pragma once
#include <raylib.h>

const char windowTitle[] = "Dungeon Fighter";
const int windowWidth = 800, windowHeight = 800;
const int gameWidth = windowWidth, gameHeight = windowHeight / 2;

typedef struct Ship
{
    float xPos, yPos, width, height, accel, maxSpeed, xSpeed, ySpeed;
    bool isEnemy;
} Ship;

void initShip(Ship *ship, float xPos, float yPos, bool isEnemy)
{
    ship->isEnemy = isEnemy;
    ship->width = 40;
    ship->height = 60;
    ship->xPos = xPos;
    ship->yPos = ship->isEnemy ? yPos : yPos - ship->height;
    ship->accel = 25;
    ship->maxSpeed = 250;
    ship->xSpeed = 0;
    ship->ySpeed = 0;
}

void drawShip(Ship *ship, Color color)
{
    DrawRectangle(ship->xPos, ship->yPos, ship->width, ship->height, color);
}

static void accelerate(int a, int b, float *speed, Ship *ship)
{
    if (IsKeyDown(a))
    {
        if (*speed > -ship->maxSpeed)
        {
            *speed -= ship->accel;
            if (*speed < -ship->maxSpeed)
                *speed = -ship->maxSpeed;
        }
    }
    else if (IsKeyDown(b))
    {
        if (*speed < ship->maxSpeed)
        {
            *speed += ship->accel;
            if (*speed > ship->maxSpeed)
                *speed = ship->maxSpeed;
        }
    }
    else if (*speed < 0)
    {
        *speed += ship->accel;
        if (*speed > 0)
            *speed = 0;
    }
    else if (*speed > 0)
    {
        *speed -= ship->accel;
        if (*speed < 0)
            *speed = 0;
    }
}

void moveShip(Ship *ship)
{
    int *moves = (ship->isEnemy) ? (int[]){KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP} : (int[]){KEY_A, KEY_D, KEY_W, KEY_S};

    accelerate(moves[0], moves[1], &(ship->xSpeed), ship);
    accelerate(moves[2], moves[3], &ship->ySpeed, ship);

    float frameDelta = GetFrameTime();
    ship->xPos += ship->xSpeed * frameDelta;
    ship->yPos += ship->ySpeed * frameDelta;

    if (ship->xPos < 0)
        ship->xPos = 0;
    else if (ship->xPos > gameWidth - ship->width)
        ship->xPos = gameWidth - ship->width;

    if (ship->isEnemy)
    {
        if (ship->yPos < 0)
            ship->yPos = 0;
        else if (ship->yPos > gameHeight - ship->height)
            ship->yPos = gameHeight - ship->height;
    }
    else
    {
        if (ship->yPos < gameHeight)
            ship->yPos = gameHeight;
        else if (ship->yPos > windowHeight - ship->height)
            ship->yPos = windowHeight - ship->height;
    }
}
