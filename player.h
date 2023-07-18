#pragma once
#include "utils.h"

struct Player
{
    float xPos, yPos, width, height, accel, maxSpeed, xSpeed, ySpeed;
    bool isEnemy;
};

void initPlayer(struct Player *player, float xPos, float yPos, bool isEnemy)
{
    player->isEnemy = isEnemy;
    player->width = 40;
    player->height = 60;
    player->xPos = xPos;
    player->yPos = player->isEnemy ? yPos : yPos - player->height;
    player->accel = 25;
    player->maxSpeed = 250;
    player->xSpeed = 0;
    player->ySpeed = 0;
}

void drawPlayer(struct Player *player, Color color)
{
    DrawRectangle(player->xPos, player->yPos, player->width, player->height, color);
}

static void accel(int a, int b, float *speed, struct Player *player)
{
    if (IsKeyDown(a))
    {
        if (*speed > -player->maxSpeed)
        {
            *speed -= player->accel;
            if (*speed < -player->maxSpeed)
                *speed = -player->maxSpeed;
        }
    }
    else if (IsKeyDown(b))
    {
        if (*speed < player->maxSpeed)
        {
            *speed += player->accel;
            if (*speed > player->maxSpeed)
                *speed = player->maxSpeed;
        }
    }
    else if (*speed < 0)
    {
        *speed += player->accel;
        if (*speed > 0)
            *speed = 0;
    }
    else if (*speed > 0)
    {
        *speed -= player->accel;
        if (*speed < 0)
            *speed = 0;
    }
}

void movePlayer(struct Player *player)
{
    int *moves = (player->isEnemy) ? (int[]){KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP} : (int[]){KEY_A, KEY_D, KEY_W, KEY_S};

    accel(moves[0], moves[1], &(player->xSpeed), player);
    accel(moves[2], moves[3], &player->ySpeed, player);

    float frameDelta = GetFrameTime();
    player->xPos += player->xSpeed * frameDelta;
    player->yPos += player->ySpeed * frameDelta;

    if (player->xPos < 0)
        player->xPos = 0;
    else if (player->xPos > gameWidth - player->width)
        player->xPos = gameWidth - player->width;

    if (player->isEnemy)
    {
        if (player->yPos < 0)
            player->yPos = 0;
        else if (player->yPos > gameHeight - player->height)
            player->yPos = gameHeight - player->height;
    }
    else
    {
        if (player->yPos < gameHeight)
            player->yPos = gameHeight;
        else if (player->yPos > windowHeight - player->height)
            player->yPos = windowHeight - player->height;
    }
}

// debug
#include <stdio.h>
void drawPlayerSpeeds(struct Player player, struct Player enemy)
{
    int max = 100;
    char text[max];

    snprintf(text, max, "%f | %f", enemy.xSpeed, enemy.ySpeed);
    DrawText(text, 0, 0, 32, BLACK);

    snprintf(text, max, "%f | %f", player.xSpeed, player.ySpeed);
    DrawText(text, 0, gameHeight, 32, BLACK);
}