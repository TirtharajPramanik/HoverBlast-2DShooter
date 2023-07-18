#include "player.h"

struct Player enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    initPlayer(&enemy, windowWidth / 2, 0, true);
    initPlayer(&player, windowWidth / 2, windowHeight, false);

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(30);
    while (!WindowShouldClose())
    {
        updateFrame();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawFrame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void updateFrame(void)
{
    movePlayer(&enemy);
    movePlayer(&player);
}

void drawFrame(void)
{
    // center divider
    DrawLine(0, gameHeight, gameWidth, gameHeight, BLUE);
    // debug
    drawPlayerSpeeds(player, enemy);

    drawPlayer(&enemy, BLUE);
    drawPlayer(&player, MAROON);
}