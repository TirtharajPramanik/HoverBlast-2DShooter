#pragma once
#include "ship.h"
#include <stdio.h>
#define FONTSIZE 16

void drawShipSpeednHealth(int args, ...)
{
    int max = 100;
    char text[max];
    va_list ap;
    va_start(ap, args);
    for (int i = 0; i < args; i++)
    {
        Ship ship = va_arg(ap, Ship);
        snprintf(text, max, "X: %f | Y: %f | H: %d | S: %d",
                 ship.xSpeed, ship.ySpeed, ship.health, ship.score);
        DrawText(text, 0, arenaHeight() + (ship.isEnemy ? -FONTSIZE : 0), FONTSIZE, BLACK);
    }
    va_end(ap);
}

void drawShipPosition(int args, ...)
{
    int max = 100;
    char text[max];
    va_list ap;
    va_start(ap, args);
    for (int i = 0; i < args; i++)
    {
        Ship ship = va_arg(ap, Ship);
        snprintf(text, max, "X: %f", ship.rect.x);
        DrawText(text, ship.rect.x + ship.rect.width / 2 - MeasureText(text, FONTSIZE) / 2,
                 ship.rect.y + (ship.isEnemy ? ship.rect.height : -FONTSIZE), FONTSIZE, BLACK);
        snprintf(text, max, "Y: %f", ship.rect.y);
        DrawTextPro(GetFontDefault(), text,
                    (Vector2){ship.rect.x + (ship.isEnemy ? -FONTSIZE : 0),
                              ship.rect.y + (ship.isEnemy ? ship.rect.height : -FONTSIZE) + (ship.isEnemy ? 0 : FONTSIZE)},
                    (Vector2){0, 0}, ship.isEnemy ? -90 : 90, FONTSIZE, 1, BLACK);
    }
    va_end(ap);
}

void drawShotsSpeednPositions(int args, ...)
{
    int max = 100;
    char text[max];
    va_list ap;
    va_start(ap, args);
    for (int i = 0; i < args; i++)
    {
        Ship ship = va_arg(ap, Ship);
        for (int i = 0; i < maxShots; i++)
        {
            snprintf(text, max, "X: %f | Y: %f | S: %f",
                     ship.shots[i].pos.x, ship.shots[i].pos.y, ship.shots[i].speed);
            DrawText(text, gameWidth() - MeasureText(text, FONTSIZE),
                     arenaHeight() + 12 * (ship.isEnemy ? -(i + 1) : i), FONTSIZE, BLACK);
        }
    }
    va_end(ap);
}

void drawShipnShotsBounds(int args, ...)
{
    int max = 100;
    char text[max];
    va_list ap;
    va_start(ap, args);
    for (int i = 0; i < args; i++)
    {
        Ship ship = va_arg(ap, Ship);
        DrawRectangleLines(ship.rect.x, ship.rect.y, ship.rect.width, ship.rect.height, RED);
        for (int i = 0; i < maxShots; i++)
            if (ship.shots[i].active)
                DrawCircleLines(ship.shots[i].pos.x, ship.shots[i].pos.y, ship.shots[i].colider, RED);
    }
}
