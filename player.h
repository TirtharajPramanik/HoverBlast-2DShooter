#pragma once
#include "utils.h"

struct Player
{
    float xPos, yPos, width, height, speed, accel, maxSpeed, xDelta, yDelta;
};

void initPlayer(struct Player *player, float xPos, float yPos, float width, float height, float accel)
{
    player->xPos = xPos;
    player->yPos = yPos;
    player->width = width;
    player->height = height;
    player->accel = accel;
    player->maxSpeed = 10000;
    player->speed = 0;
    player->xDelta = 0;
    player->yDelta = 0;
}

void drawPlayer(struct Player *player, Color color)
{
    DrawRectangle(player->xPos, player->yPos, player->width, player->height, color);
}

void moveEnemy(struct Player *player)
{
    bool xAccel = true, yAccel = true;

    if (IsKeyDown(KEY_UP))
        player->yDelta = 1, player->xDelta = 0;
    else if (IsKeyDown(KEY_DOWN))
        player->yDelta = -1, player->xDelta = 0;
    else
        yAccel = false;

    if (IsKeyDown(KEY_LEFT))
        player->xDelta = 1, player->yDelta = 0;
    else if (IsKeyDown(KEY_RIGHT))
        player->xDelta = -1, player->yDelta = 0;
    else
        xAccel = false;

    if (xAccel || yAccel)
    {
        if (player->speed < player->maxSpeed)
        {
            player->speed += player->accel;
            if (player->speed > player->maxSpeed)
                player->speed = player->maxSpeed;
        }
    }
    else if (player->speed > 0)
    {
        player->speed -= player->accel;
        if (player->speed < 0)
            player->speed = 0;
    }

    float frameDelta = player->speed * GetFrameTime();
    player->xPos += player->xDelta * frameDelta;
    player->yPos += player->yDelta * frameDelta;

    if (player->xPos < 0)
        player->xPos = 0;
    else if (player->xPos > gameWidth - player->width)
        player->xPos = gameWidth - player->width;

    if (player->yPos < 0)
        player->yPos = 0;
    else if (player->yPos > gameHeight - player->height)
        player->yPos = gameHeight - player->height;
}
