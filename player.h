#pragma once
#include "utils.h"

struct Player
{
    float xPos, yPos, width, height, accel, maxSpeed, xSpeed, ySpeed;
};

void initPlayer(struct Player *player, float xPos, float yPos, float width, float height, float accel, float maxSpeed)
{
    player->xPos = xPos;
    player->yPos = yPos;
    player->width = width;
    player->height = height;
    player->accel = accel;
    player->maxSpeed = maxSpeed;
    player->xSpeed = 0;
    player->ySpeed = 0;
}

void drawPlayer(struct Player *player, Color color)
{
    DrawRectangle(player->xPos, player->yPos, player->width, player->height, color);
}

void movePlayer(struct Player *player)
{
    int *moves = (player->yPos > gameHeight) ? (int[]){KEY_A, KEY_D, KEY_W, KEY_S} : (int[]){KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP};

    if (IsKeyDown(moves[0]))
    {
        if (player->xSpeed > -player->maxSpeed)
        {
            player->xSpeed -= player->accel;
            if (player->xSpeed < -player->maxSpeed)
                player->xSpeed = -player->maxSpeed;
        }
    }
    else
    {
        if (player->xSpeed < 0)
        {
            player->xSpeed += player->accel;
            if (player->xSpeed > 0)
                player->xSpeed = 0;
        }
    }

    if (IsKeyDown(moves[2]))
    {
        if (player->ySpeed > -player->maxSpeed)
        {
            player->ySpeed -= player->accel;
            if (player->ySpeed < -player->maxSpeed)
                player->ySpeed = -player->maxSpeed;
        }
    }
    else
    {
        if (player->ySpeed < 0)
        {
            player->ySpeed += player->accel;
            if (player->ySpeed > 0)
                player->ySpeed = 0;
        }
    }

    float frameDelta = GetFrameTime();
    player->xPos += player->xSpeed * frameDelta;
    player->yPos += player->ySpeed * frameDelta;

    if (player->xPos < 0)
        player->xPos = 0;
    else if (player->xPos > gameWidth - player->width)
        player->xPos = gameWidth - player->width;

    if (player->yPos > gameHeight)
    {
        if (player->yPos < gameHeight)
            player->yPos = gameHeight;
        else if (player->yPos > windowHeight - player->height)
            player->yPos = windowHeight - player->height;
    }
    else
    {
        if (player->yPos < 0)
            player->yPos = 0;
        else if (player->yPos > gameHeight - player->height)
            player->yPos = gameHeight - player->height;
    }
}
