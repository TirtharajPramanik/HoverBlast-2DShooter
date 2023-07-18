#pragma once
#include "utils.h"

struct Player
{
    float xPos, yPos, width, height, accel, xSpeed, ySpeed;
};

void initPlayer(struct Player *player, float xPos, float yPos, float width, float height, float accel)
{
    player->xPos = xPos;
    player->yPos = yPos;
    player->width = width;
    player->height = height;
    player->accel = accel;
    player->xSpeed = 0;
    player->ySpeed = 0;
}

void drawPlayer(struct Player *player, Color color)
{
    DrawRectangle(player->xPos, player->yPos, player->width, player->height, color);
}

void movePlayer(struct Player *player, int posDelta)
{
    int *moves = (posDelta == -1) ? (int[]){KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN} : (int[]){KEY_A, KEY_D, KEY_W, KEY_S};

    bool xAccel = true, yAccel = true;

    if (IsKeyDown(moves[0]))
        player->xSpeed -= player->accel;
    else if (IsKeyDown(moves[1]))
        player->xSpeed += player->accel;
    else
        xAccel = false;

    if (IsKeyDown(moves[2]))
        player->ySpeed -= player->accel;
    else if (IsKeyDown(moves[3]))
        player->ySpeed += player->accel;
    else
        yAccel = false;

    if (xAccel)
    {
        if (player->xSpeed > maxSpeed)
            player->xSpeed = maxSpeed;
        else if (player->xSpeed < -maxSpeed)
            player->xSpeed = -maxSpeed;
    }
    if (yAccel)
    {
        if (player->ySpeed > maxSpeed)
            player->ySpeed = maxSpeed;
        else if (player->ySpeed < -maxSpeed)
            player->ySpeed = -maxSpeed;
    }

    float frameDelta = GetFrameTime() * posDelta;
    player->xPos += player->xSpeed * frameDelta;
    player->yPos += player->ySpeed * frameDelta;

    if (player->xPos < 0)
        player->xPos = 0;
    else if (player->xPos > gameWidth - player->width)
        player->xPos = gameWidth - player->width;

    if (posDelta == -1)
    {
        if (player->yPos < 0)
            player->yPos = 0;
        else if (player->yPos > gameHeight - player->height)
            player->yPos = gameHeight - player->height;
    }
    else
    {
        if (player->yPos < 0)
            player->yPos = 0;
        else if (player->yPos < gameHeight)
            player->yPos = gameHeight;
    }
}
