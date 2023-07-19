#include "ship.h"
#include "debug.h"

Ship enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(60);

    Texture2D shipTexture = LoadTexture("assets/Ship.png");
    Texture2D redShotTexture = LoadTexture("assets/RedShot.png");
    Texture2D blueShotTexture = LoadTexture("assets/BlueShot.png");

    initShip(&enemy, gameWidth / 2, 0, true, &shipTexture, &redShotTexture);
    initShip(&player, gameWidth / 2, windowHeight, false, &shipTexture, &blueShotTexture);

    while (!WindowShouldClose())
    {
        updateFrame();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawFrame();
        EndDrawing();
    }

    UnloadTexture(blueShotTexture);
    UnloadTexture(redShotTexture);
    UnloadTexture(shipTexture);

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
    // rail tracks
    DrawLine(0, gameHeight, gameWidth, gameHeight, BLUE);

    drawShip(&enemy);
    drawShip(&player);

    for (int i = 0; i < maxShots; i++)
    {
        drawShot(&enemy.shots[i]);
        drawShot(&player.shots[i]);
    }

    // debug
    drawShipSpeed(2, enemy, player);
    drawShipPosition(2, enemy, player);
    drawShipShotsSpeednPositions(2, enemy, player);
}
