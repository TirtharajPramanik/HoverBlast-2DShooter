#pragma once
#include "shot.h"

typedef struct
{
    Rectangle rect;
    float accel, xSpeed, ySpeed;
    bool isEnemy, explode;
    Shot shots[maxShots];
    Texture2D texture;
    int score, health, fireRate, lastShootFrame;
} Ship;

void initShip(Ship *ship, float xPos, float yPos, bool isEnemy, Texture2D *shipTexture, Texture2D *shotTexture)
{
    ship->accel = 50;
    ship->xSpeed = 0;
    ship->ySpeed = 0;
    ship->score = 0;
    ship->health = 10;
    ship->lastShootFrame = 0;
    ship->texture = *shipTexture;
    ship->rect.width = shipTexture->width * 1.4;
    ship->rect.height = shipTexture->height * 1.4;
    ship->explode = false;
    ship->isEnemy = isEnemy;
    ship->rect.x = xPos;
    ship->rect.y = ship->isEnemy ? yPos : yPos - ship->rect.height;
    ship->fireRate = maxShots / 4;
    for (int i = 0; i < maxShots; i++)
        initShot(&ship->shots[i], 0, 0, 6, shotTexture);
}

void drawShip(Ship *ship)
{
    DrawTextureEx(ship->texture,
                  ship->isEnemy ? (Vector2){ship->rect.x + ship->rect.width, ship->rect.y + ship->rect.height}
                                : (Vector2){ship->rect.x, ship->rect.y},
                  ship->isEnemy ? 180 : 0, ship->rect.width / ship->texture.width, WHITE);
}

static void accelerate(int xAxis, int yAxis, float *speed, float accel, float maxShipSpeed)
{
    if (IsKeyDown(xAxis))
    {
        if (*speed > -maxShipSpeed)
        {
            *speed -= accel;
            if (*speed < -maxShipSpeed)
                *speed = -maxShipSpeed;
        }
    }
    else if (IsKeyDown(yAxis))
    {
        if (*speed < maxShipSpeed)
        {
            *speed += accel;
            if (*speed > maxShipSpeed)
                *speed = maxShipSpeed;
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
    int *moves = (ship->isEnemy) ? (int[]){KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP}
                                 : (int[]){KEY_A, KEY_D, KEY_W, KEY_S};

    accelerate(moves[0], moves[1], &ship->xSpeed, ship->accel, maxShipSpeed);
    accelerate(moves[2], moves[3], &ship->ySpeed, ship->accel, maxShipSpeed);

    float frameDelta = GetFrameTime();
    ship->rect.x += ship->xSpeed * frameDelta;
    ship->rect.y += ship->ySpeed * frameDelta;

    if (ship->rect.x < 0)
        ship->rect.x = 0;
    else if (ship->rect.x > gameWidth() - ship->rect.width)
        ship->rect.x = gameWidth() - ship->rect.width;

    if (ship->isEnemy)
    {
        if (ship->rect.y < 0)
            ship->rect.y = 0;
        else if (ship->rect.y > arenaHeight() - ship->rect.height)
            ship->rect.y = arenaHeight() - ship->rect.height;
    }
    else
    {
        if (ship->rect.y < arenaHeight())
            ship->rect.y = arenaHeight();
        else if (ship->rect.y > gameHeight() - ship->rect.height)
            ship->rect.y = gameHeight() - ship->rect.height;
    }
}

void shoot(Ship *ship)
{
    if (ship->lastShootFrame < frameRate / ship->fireRate)
        ship->lastShootFrame++;
    else if (IsKeyDown(ship->isEnemy ? KEY_F : KEY_SPACE))
    {
        ship->lastShootFrame = 0;
        for (int i = 0; i < maxShots; i++)
            if (!ship->shots[i].active)
            {
                ship->shots[i].pos.x = ship->rect.x + ship->rect.width / 2;
                ship->shots[i].pos.y = ship->rect.y + (ship->isEnemy ? ship->rect.height : 0);
                ship->shots[i].toDown = ship->isEnemy;
                ship->shots[i].speed = maxShipSpeed;
                ship->shots[i].active = true;
                break;
            };
    }
}
