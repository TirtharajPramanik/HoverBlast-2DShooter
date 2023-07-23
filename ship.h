#pragma once
#include "shot.h"

typedef struct
{
    Rectangle rect;
    Shot shots[maxShots];
    float accel, xSpeed, ySpeed;
    bool isEnemy, alive, blastSoundPlayed;
    int score, health, fireRate, lastShootFrame,
        lastBlastFrame, currentBlastRect, totalBlastRects;
} Ship;

void initShip(Ship *ship, float xPos, float yPos, bool isEnemy)
{
    ship->accel = 50;
    ship->xSpeed = 0;
    ship->ySpeed = 0;
    ship->score = 0;
    ship->health = 10;
    ship->alive = true;
    ship->rect.x = xPos;
    ship->isEnemy = isEnemy;
    ship->lastShootFrame = 0;
    ship->lastBlastFrame = 0;
    ship->totalBlastRects = 8;
    ship->currentBlastRect = 0;
    ship->fireRate = maxShots / 4;
    ship->blastSoundPlayed = false;
    ship->rect.width = shipTexture.width * 1.4;
    ship->rect.height = shipTexture.height * 1.4;
    ship->rect.y = ship->isEnemy ? yPos : yPos - ship->rect.height;
    for (int i = 0; i < maxShots; i++)
        initShot(&ship->shots[i], 0, 0, 6);
}

void drawShip(Ship *ship)
{
    (DrawTextureEx(shipTexture,
                   ship->isEnemy ? (Vector2){ship->rect.x + ship->rect.width, ship->rect.y + ship->rect.height}
                                 : (Vector2){ship->rect.x, ship->rect.y},
                   ship->isEnemy ? 180 : 0, ship->rect.width / shipTexture.width, WHITE));
}

void drawBlast(Ship *ship)
{
    float blastSpan = shipBlastTexture.height;
    DrawTextureRec(shipBlastTexture,
                   (Rectangle){blastSpan * ship->currentBlastRect, 0, blastSpan, blastSpan},
                   (Vector2){ship->rect.x, ship->rect.y}, WHITE);
}

bool overBlast(Ship *ship)
{
    if (!ship->blastSoundPlayed)
        PlaySound(blastSound), ship->blastSoundPlayed = true;
    bool ret = false;
    if (ship->lastBlastFrame < (frameRate / ship->totalBlastRects))
        ship->lastBlastFrame++;
    else
    {
        (ship->lastBlastFrame = 0),
            (ship->currentBlastRect < ship->totalBlastRects)
                ? ship->currentBlastRect++
                : (ret = true);
    }
    return ret;
}

void drawShipStats(Ship *ship)
{
    drawStats(ship->isEnemy ? "Enemy" : "Player", ship->score, ship->health,
              ship->isEnemy ? 24 : GetScreenHeight() - 24 * 4, 24, ship->isEnemy ? RED : BLUE);
}

static void accelerate(float *speed, int xAxis, int yAxis, float accel)
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

    accelerate(&ship->xSpeed, moves[0], moves[1], ship->accel);
    accelerate(&ship->ySpeed, moves[2], moves[3], ship->accel);

    float frameDelta = GetFrameTime();
    ship->rect.x += ship->xSpeed * frameDelta;
    ship->rect.y += ship->ySpeed * frameDelta;

    // horizontal collision
    if (ship->rect.x < 0)
        ship->xSpeed < 0 ? (ship->xSpeed *= -1) : (ship->rect.x = 0);
    else if (ship->rect.x > arenaWidth() - ship->rect.width)
        ship->xSpeed > 0 ? (ship->xSpeed *= -1) : (ship->rect.x = arenaWidth() - ship->rect.width);

    // vertical collision
    if (ship->rect.y < (ship->isEnemy ? 0 : arenaHeight()))
        ship->ySpeed < 0 ? (ship->ySpeed *= -1) : (ship->rect.y = (ship->isEnemy ? 0 : arenaHeight()));
    else if (ship->rect.y > (ship->isEnemy ? arenaHeight() : GetScreenHeight()) - ship->rect.height)
        ship->ySpeed > 0 ? (ship->ySpeed *= -1) : (ship->rect.y = (ship->isEnemy ? arenaHeight() : GetScreenHeight()) - ship->rect.height);
}

void shoot(Ship *ship)
{
    if (ship->lastShootFrame < frameRate / ship->fireRate)
        ship->lastShootFrame++;
    else if (IsKeyDown(ship->isEnemy ? KEY_F : KEY_SPACE))
    {
        PlaySound(shootSound);
        ship->lastShootFrame = 0;
        for (int i = 0; i < maxShots; i++)
            if (!ship->shots[i].active)
            {
                ship->shots[i].pos.x = ship->rect.x + ship->rect.width / 2;
                ship->shots[i].pos.y = ship->rect.y + (ship->isEnemy ? ship->rect.height : 0);
                ship->shots[i].fromEnemy = ship->isEnemy;
                ship->shots[i].speed = maxShipSpeed;
                ship->shots[i].active = true;
                break;
            };
    }
}
