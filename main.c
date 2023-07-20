#include "ship.h"
#include "debug.h"

bool running;
Ship enemy, player;
Texture2D shipTexture, redShotTexture, blueShotTexture;

void drawMenu(void);
void drawGame(void);
void resetGame(void);
void updateGame(void);

int main(void)
{
    InitWindow(windowWidth, windowHeight, windowTitle);

    shipTexture = LoadTexture("assets/Ship.png");
    redShotTexture = LoadTexture("assets/RedShot.png");
    blueShotTexture = LoadTexture("assets/BlueShot.png");

    resetGame();
    SetTargetFPS(frameRate);

    while (!WindowShouldClose())
        if (running)
            updateGame(), drawGame();
        else
            drawMenu();

    UnloadTexture(blueShotTexture);
    UnloadTexture(redShotTexture);
    UnloadTexture(shipTexture);

    CloseWindow();
    return 0;
}

void resetGame(void)
{
    initShip(&enemy, gameWidth / 2, 0, true, &shipTexture, &redShotTexture);
    initShip(&player, gameWidth / 2, windowHeight, false, &shipTexture, &blueShotTexture);
    running = true;
}

void updateGame(void)
{
    (enemy.health <= 0 || player.health <= 0) ? running = false : 0;

    moveShip(&enemy);
    moveShip(&player);

    // handle shooting & damage
    for (int i = 0; i < maxShots; i++)
    {
        moveShot(&enemy.shots[i]);
        moveShot(&player.shots[i]);

        if (checkShot(&player.shots[i], enemy.rect))
            player.score++, enemy.health--;
        if (checkShot(&enemy.shots[i], player.rect))
            enemy.score++, player.health--;
    }

    shoot(&enemy);
    shoot(&player);
}

void drawMenu(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    IsKeyPressed(KEY_ENTER) ? resetGame() : 0;

    char gameOverText[] = "Game Over";
    DrawText(gameOverText, gameWidth / 2 - MeasureText(gameOverText, 24) / 2, gameHeight - 24, 24, BLUE);

    char replayText[] = "Press Enter to Replay";
    DrawText(replayText, gameWidth / 2 - MeasureText(replayText, 24) / 2, gameHeight, 24, GREEN);

    EndDrawing();
}

void drawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // center divider
    DrawLine(0, gameHeight, gameWidth, gameHeight, BLUE);

    drawShip(&enemy);
    drawShip(&player);

    for (int i = 0; i < maxShots; i++)
    {
        drawShot(&enemy.shots[i]);
        drawShot(&player.shots[i]);
    }

#ifdef DEBUG
    drawShotsSpeednPositions(2, enemy, player);
    drawShipnShotsBounds(2, enemy, player);
    drawShipSpeednHealth(2, enemy, player);
    drawShipPosition(2, enemy, player);
#endif

    EndDrawing();
}
