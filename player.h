#pragma once
#include "utils.h"

struct Ship
{
    int xCellPos, yCellPos, speed;
};

struct Ship initPlayer(int xCellPos, int yCellPos, int speed)
{
    struct Ship player;
    player.speed = speed;
    player.xCellPos = xCellPos;
    player.yCellPos = yCellPos;
    return player;
}

void drawPlayer(struct Ship *player, Color color)
{
    DrawRectangle(player->xCellPos * cellWidth, player->yCellPos * cellHeight, cellWidth, cellHeight, color);
}

void movePlayer(struct Ship *player)
{
    if (IsKeyPressed(KEY_W) &&
        player->yCellPos > game_yCellCount)
        player->yCellPos -= player->speed;
    if (IsKeyPressed(KEY_S) &&
        player->yCellPos < window_yCellCount - 1)
        player->yCellPos += player->speed;
    if (IsKeyPressed(KEY_A) &&
        player->xCellPos > 0)
        player->xCellPos -= player->speed;
    if (IsKeyPressed(KEY_D) &&
        player->xCellPos < game_xCellCount - 1)
        player->xCellPos += player->speed;
}

void moveEnemy(struct Ship *player)
{
    if (IsKeyPressed(KEY_UP) &&
        player->yCellPos < game_yCellCount - 1)
        player->yCellPos -= player->speed;
    if (IsKeyPressed(KEY_DOWN) &&
        player->yCellPos > 0)
        player->yCellPos += player->speed;
    if (IsKeyPressed(KEY_LEFT) &&
        player->xCellPos < game_xCellCount - 1)
        player->xCellPos -= player->speed;
    if (IsKeyPressed(KEY_RIGHT) &&
        player->xCellPos > 0)
        player->xCellPos += player->speed;
}
