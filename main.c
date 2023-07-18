#include "player.h"

#define W 40
#define H 60
#define A 100

struct Player enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    initPlayer(&enemy, windowWidth / 2, 0, W, H, A);
    initPlayer(&player, windowWidth / 2, windowHeight - H, W, H, A);

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
    moveEnemy(&enemy);

    // movePlayer(&player);
}

void drawFrame(void)
{
    // center divider
    DrawLine(0, gameHeight, gameWidth, gameHeight, BLUE);

    drawPlayer(&enemy, BLUE);

    drawPlayer(&player, MAROON);
}