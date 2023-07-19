#pragma once
#include "consts.h"

typedef struct
{
    float xPos, yPos, speed, accel, maxSpeed;
    bool active, toDown;
    Texture2D texture;
} Shot;

void drawShot(Shot *shot)
{
    if (shot->active)
        DrawTextureEx(shot->texture, (Vector2){shot->xPos + shot->texture.width / 2 * (shot->toDown ? 1 : -1), shot->yPos}, shot->toDown ? 90 : -90, 1, WHITE);
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
