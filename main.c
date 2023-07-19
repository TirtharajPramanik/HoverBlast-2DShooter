#include "game.h"
#include "debug.h"

Train train;
Ship enemy, player;

void drawFrame(void);
void updateFrame(void);

int main(void)
{
    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(30);

    Texture2D shipTexture = LoadTexture("assets/Ship.png");
    Texture2D engineTexture = LoadTexture("assets/Engine.png");
    Texture2D ammoCabinTexture = LoadTexture("assets/AmmoCabin.png");
    Texture2D bombCabinTexture = LoadTexture("assets/BombCabin.png");
    Texture2D healthCabinTexture = LoadTexture("assets/HealthCabin.png");

    initShip(&enemy, gameWidth / 2, 0, true, &shipTexture);
    initShip(&player, gameWidth / 2, windowHeight, false, &shipTexture);
    initTrain(&train, 200, gameHeight, &engineTexture, &bombCabinTexture, &ammoCabinTexture, &healthCabinTexture);

    while (!WindowShouldClose())
    {
        updateFrame();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawFrame();
        EndDrawing();
    }

    UnloadTexture(healthCabinTexture);
    UnloadTexture(bombCabinTexture);
    UnloadTexture(ammoCabinTexture);
    UnloadTexture(engineTexture);
    UnloadTexture(shipTexture);

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
    // rail tracks
    DrawLine(0, gameHeight, gameWidth, gameHeight, RED);
    DrawLine(0, gameHeight + railWidth, gameWidth, gameHeight + railWidth, BLUE);

    drawShip(&enemy);
    drawShip(&player);
    drawTrain(&train);

    // debug
    drawShipSpeed(2, enemy, player);
    drawShipPosition(2, enemy, player);
}