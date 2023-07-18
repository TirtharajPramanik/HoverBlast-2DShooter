#include "game.h"
#include "debug.h"

Ship enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    initShip(&enemy, windowWidth / 2, 0, true);
    initShip(&player, windowWidth / 2, windowHeight, false);

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
    moveShip(&enemy);
    moveShip(&player);
}

void drawFrame(void)
{
    // center divider
    DrawLine(0, gameHeight, gameWidth, gameHeight, BLUE);

    drawShip(&enemy, BLUE);
    drawShip(&player, MAROON);

    // debug
    drawShipSpeed(2, enemy, player);
    drawShipPosition(2, enemy, player);
}