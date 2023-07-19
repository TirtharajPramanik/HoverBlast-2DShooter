#include "ship.h"
#include "debug.h"

Ship enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    initShip(&enemy, windowWidth / 2, 0, true);
    initShip(&player, windowWidth / 2, windowHeight, false);

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(60);
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

    for (int i = 0; i < maxShots; i++)
    {
        moveShot(&enemy.shots[i]);
        moveShot(&player.shots[i]);
    }

    shoot(&enemy);
    shoot(&player);
}

void drawFrame(void)
{
    // center divider
    DrawLine(0, gameHeight, gameWidth, gameHeight, BLUE);

    drawShip(&enemy, BLUE);
    drawShip(&player, MAROON);

    for (int i = 0; i < maxShots; i++)
    {
        drawShot(&enemy.shots[i], BLUE);
        drawShot(&player.shots[i], MAROON);
    }

    // debug
    drawShipSpeed(2, enemy, player);
    drawShipPosition(2, enemy, player);
    drawShipShotsSpeednPositions(2, enemy, player);
}
