#pragma once
#include "shot.h"

typedef struct
{
    Rectangle rect;
    float accel, maxSpeed, xSpeed, ySpeed;
    bool isEnemy, explode;
    Shot shots[maxShots];
    Texture2D texture;
    int score, health;
} Ship;

void initShip(Ship *ship, float xPos, float yPos, bool isEnemy, Texture2D *shipTexture, Texture2D *shotTexture)
{
    ship->texture = *shipTexture;
    ship->rect.width = shipTexture->width;
    ship->rect.x = xPos;
    ship->rect.height = shipTexture->height;
    ship->explode = false;
    ship->isEnemy = isEnemy;
    ship->rect.y = ship->isEnemy ? yPos : yPos - ship->rect.height;
    ship->accel = 50;
    ship->maxSpeed = 500;
    ship->xSpeed = 0;
    ship->ySpeed = 0;
    ship->score = 0;
    ship->health = 10;
    for (int i = 0; i < maxShots; i++)
        initShot(&ship->shots[i], 0, 0, 6, 600, shotTexture);
}

void drawShip(Ship *ship)
{
    DrawTextureEx(ship->texture,
                  (ship->isEnemy ? (Vector2){ship->rect.x + ship->rect.width, ship->rect.y + ship->rect.height}
                                 : (Vector2){ship->rect.x, ship->rect.y}),
                  ship->isEnemy ? 180 : 0, 1, WHITE);
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
    ship->rect.x += ship->xSpeed * frameDelta;
    ship->rect.y += ship->ySpeed * frameDelta;

    if (ship->rect.x < 0)
        ship->rect.x = 0;
    else if (ship->rect.x > gameWidth - ship->rect.width)
        ship->rect.x = gameWidth - ship->rect.width;

    if (ship->isEnemy)
    {
        if (ship->rect.y < 0)
            ship->rect.y = 0;
        else if (ship->rect.y > gameHeight - ship->rect.height)
            ship->rect.y = gameHeight - ship->rect.height;
    }
    else
    {
        if (ship->rect.y < gameHeight)
            ship->rect.y = gameHeight;
        else if (ship->rect.y > windowHeight - ship->rect.height)
            ship->rect.y = windowHeight - ship->rect.height;
    }
}

void shoot(Ship *ship)
{
    if (IsKeyPressed(ship->isEnemy ? KEY_F : KEY_SPACE))
        for (int i = 0; i < maxShots; i++)
            if (!ship->shots[i].active)
            {
                ship->shots[i].rect.x = ship->rect.x + ship->rect.width / 2;
                ship->shots[i].rect.y = ship->rect.y + (ship->isEnemy ? ship->rect.height : 0);
                ship->shots[i].toDown = ship->isEnemy;
                ship->shots[i].speed = ship->maxSpeed;
                ship->shots[i].active = true;
                break;
            }
}
