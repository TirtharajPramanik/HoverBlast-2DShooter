#pragma once
#include "setting.h"

typedef struct
{
    Vector2 pos;
    float radius, colider, speed, accel;
    bool active, toDown;
    Texture2D texture;
} Shot;

void initShot(Shot *shot, float xPos, float yPos, float accel, Texture2D *texture)
{
    shot->pos.x = xPos;
    shot->pos.y = yPos;
    shot->texture = *texture;
    shot->radius = texture->height / 2;
    shot->colider = texture->height / 3;
    shot->speed = 0;
    shot->accel = accel;
    shot->active = false;
    shot->toDown = false;
}

void drawShot(Shot *shot)
{
    if (shot->active)
        DrawTextureEx(shot->texture,
                      (Vector2){shot->pos.x + shot->radius * (shot->toDown ? 1 : -1), shot->pos.y},
                      shot->toDown ? 90 : -90, 1, WHITE);
}

void moveShot(Shot *shot)
{
    if (shot->active)
    {
        shot->speed += shot->accel;
        if (shot->speed > maxShotSpeed)
            shot->speed = maxShotSpeed;

        shot->pos.y += shot->speed * GetFrameTime() * (shot->toDown ? 1 : -1);
        if ((shot->toDown ? shot->pos.y > GetScreenHeight() : shot->pos.y < 0))
            shot->active = false, shot->speed = 0;
    }
}

bool checkShot(Shot *shot, Rectangle rect)
{
    bool ret = false;
    if (shot->active &&
        CheckCollisionCircleRec((Vector2){shot->pos.x, shot->pos.y}, shot->colider, rect))
        shot->active = false, shot->speed = 0, ret = true;
    return ret;
}
