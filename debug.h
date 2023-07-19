#pragma once
#include "game.h"
#include <stdio.h>
#define FONTSIZE 12

void drawShipSpeed(int args, ...)
{
    int max = 100;
    char text[max];
    va_list ap;

    va_start(ap, args);
    for (int i = 0; i < args; i++)
    {
        Ship ship = va_arg(ap, Ship);
        snprintf(text, max, "X: %f | Y: %f", ship.xSpeed, ship.ySpeed);
        DrawText(text, 0, gameHeight + (ship.isEnemy ? -FONTSIZE : railWidth), FONTSIZE, BLACK);
    }
    va_end(ap);

    // snprintf(text, max, "gh: %d | rw: %d", gameHeight, railWidth);
    // DrawText(text, gameWidth - MeasureText(text, FONTSIZE), gameHeight, FONTSIZE, BLACK);
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
        snprintf(text, max, "X: %f", ship.xPos);
        DrawText(text, ship.xPos + ship.width / 2 - MeasureText(text, FONTSIZE) / 2,
                 ship.yPos + (ship.isEnemy ? ship.height : -FONTSIZE), FONTSIZE, BLACK);
        snprintf(text, max, "Y: %f", ship.yPos);
        DrawTextPro(GetFontDefault(), text,
                    (Vector2){ship.xPos + (ship.isEnemy ? -FONTSIZE : 0),
                              ship.yPos + (ship.isEnemy ? ship.height : -FONTSIZE) + (ship.isEnemy ? 0 : FONTSIZE)},
                    (Vector2){0, 0}, ship.isEnemy ? -90 : 90, FONTSIZE, 1, BLACK);
    }
    va_end(ap);
}
