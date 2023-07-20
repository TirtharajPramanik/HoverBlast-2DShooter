#pragma once
#include "consts.h"

typedef struct
{
    Rectangle rect;
    float speed, accel, maxSpeed;
    bool active, toDown;
    Texture2D texture;
} Shot;

void initShot(Shot *shot, float xPos, float yPos, float accel, float maxSpeed, Texture2D *texture)
{
    shot->rect.x = xPos;
    shot->rect.y = yPos;
    shot->texture = *texture;
    shot->rect.width = texture->width;
    shot->rect.height = texture->height;
    shot->speed = 0;
    shot->accel = accel;
    shot->maxSpeed = maxSpeed;
    shot->active = false;
    shot->toDown = false;
}

void drawShot(Shot *shot)
{
    if (shot->active)
        DrawTextureEx(shot->texture,
                      (Vector2){shot->rect.x + shot->rect.width / 2 * (shot->toDown ? 1 : -1), shot->rect.y},
                      shot->toDown ? 90 : -90, 1, WHITE);
}

void moveShot(Shot *shot)
{
    if (shot->active)
    {
        shot->speed += shot->accel;
        if (shot->speed > shot->maxSpeed)
            shot->speed = shot->maxSpeed;

        shot->rect.y += shot->speed * GetFrameTime() * (shot->toDown ? 1 : -1);
        if ((shot->toDown ? shot->rect.y > windowHeight : shot->rect.y < 0))
            shot->active = false, shot->speed = 0;
    }
}

bool checkShot(Shot *shot, Rectangle rect)
{
    bool ret = false;
    if (shot->active &&
        CheckCollisionCircleRec((Vector2){shot->rect.x, shot->rect.y}, shot->rect.height, rect))
        shot->active = false, shot->speed = 0, ret = true;
    return ret;
}
