#pragma once
#include "shot.h"

typedef struct
{
    float xPos, yPos, width, height, accel, maxSpeed, xSpeed, ySpeed;
    bool isEnemy;
    Shot shots[maxShots];
    Texture2D texture;
} Ship;

void initShip(Ship *ship, float xPos, float yPos, bool isEnemy, Texture2D *shipTexture, Texture2D *shotTexture)
{
    ship->isEnemy = isEnemy;
    ship->texture = *shipTexture;
    ship->width = shipTexture->width;
    ship->xPos = xPos;
    ship->height = shipTexture->height;
    ship->yPos = ship->isEnemy ? yPos : yPos - ship->height;
    ship->accel = 50;
    ship->maxSpeed = 500;
    ship->xSpeed = 0;
    ship->ySpeed = 0;
    for (int i = 0; i < maxShots; i++)
        ship->shots[i] = (Shot){0, 0, 0, 6, 600, false, false, *shotTexture};
}

void drawShip(Ship *ship)
{
    DrawTexturePro(ship->texture, (Rectangle){0, 0, ship->texture.width, ship->texture.height},
                   (Rectangle){ship->xPos, ship->yPos, ship->width, ship->height},
                   ship->isEnemy ? (Vector2){ship->width, ship->height} : (Vector2){0, 0},
                   ship->isEnemy ? 180 : 0, WHITE);
}

static void accelerate(int xAxis, int yAxis, float *speed, float accel, float maxSpeed)
{
    if (IsKeyDown(xAxis))
    {
        if (*speed > -maxSpeed)
        {
            *speed -= accel;
            if (*speed < -maxSpeed)
                *speed = -maxSpeed;
        }
    }
    else if (IsKeyDown(yAxis))
    {
        if (*speed < maxSpeed)
        {
            *speed += accel;
            if (*speed > maxSpeed)
                *speed = maxSpeed;
        }
    }
    else if (*speed < 0)
    {
        *speed += accel;
        if (*speed > 0)
            *speed = 0;
    }
    else if (*speed > 0)
    {
        *speed -= accel;
        if (*speed < 0)
            *speed = 0;
    }
}

void moveShip(Ship *ship)
{
    int *moves = (ship->isEnemy) ? (int[]){KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP} : (int[]){KEY_A, KEY_D, KEY_W, KEY_S};

    accelerate(moves[0], moves[1], &ship->xSpeed, ship->accel, ship->maxSpeed);
    accelerate(moves[2], moves[3], &ship->ySpeed, ship->accel, ship->maxSpeed);

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

void shoot(Ship *ship)
{
    if (IsKeyPressed(ship->isEnemy ? KEY_F : KEY_SPACE))
        for (int i = 0; i < maxShots; i++)
            if (!ship->shots[i].active)
            {
                ship->shots[i].xPos = ship->xPos + ship->width / 2; //* (ship->isEnemy ? 1 : -1);
                ship->shots[i].yPos = ship->yPos + (ship->isEnemy ? ship->height : 0);
                ship->shots[i].toDown = ship->isEnemy;
                ship->shots[i].speed = ship->maxSpeed;
                ship->shots[i].active = true;
                break;
            }
}
