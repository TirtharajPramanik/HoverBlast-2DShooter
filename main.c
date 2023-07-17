#include "player.h"

struct Ship player, enemy;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    player = initPlayer(window_xCellCount / 2, window_yCellCount - 2, 1);
    enemy = initPlayer(window_xCellCount / 2, 1, -1);

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
    movePlayer(&player);

    moveEnemy(&enemy);
}

void drawFrame(void)
{
    // center divider
    DrawLine(0, game_yCellCount * cellHeight, game_xCellCount * cellWidth, game_yCellCount * cellHeight, BLUE);

    drawPlayer(&player, MAROON);

    drawPlayer(&enemy, BLUE);
}