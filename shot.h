#pragma once
#include "consts.h"

typedef struct
{
    float xPos, yPos, speed, accel, maxSpeed;
    bool active, toDown;
} Shot;

void drawShot(Shot *shot, Color color)
{
    if (shot->active)
        DrawCircle(shot->xPos, shot->yPos, 10, color);
}

void moveShot(Shot *shot)
{
    if (shot->active)
    {
        shot->speed += shot->accel;
        if (shot->speed > shot->maxSpeed)
            shot->speed = shot->maxSpeed;

        shot->yPos += shot->speed * GetFrameTime() * (shot->toDown ? 1 : -1);
        if (shot->toDown ? shot->yPos > windowHeight : shot->yPos < 0)
            shot->active = false, shot->speed = 0;
    }
}
