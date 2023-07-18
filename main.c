#include "player.h"
#include <stdio.h>

#define W 40
#define A 10
#define S 1000
#define H 60

struct Player enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    initPlayer(&enemy, windowWidth / 2, 0, W, H, A, S);
    initPlayer(&player, windowWidth / 2, windowHeight - H, W, H, A, S);

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

    char text[S];

    snprintf(text, S, "%f | %f", enemy.xSpeed, enemy.ySpeed);
    DrawText(text, 0, 0, 32, BLACK);

    snprintf(text, S, "%f | %f", player.xSpeed, player.ySpeed);
    DrawText(text, 0, gameHeight, 32, BLACK);

    drawPlayer(&enemy, BLUE);

    drawPlayer(&player, MAROON);
}