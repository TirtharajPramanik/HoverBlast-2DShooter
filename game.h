#pragma once
#include "ship.h"

#ifdef DEBUG
#include "debug.h"
#endif

Ship enemy, player;
bool running, pause;
Texture2D shipTexture, redShotTexture, blueShotTexture;

void loadAssets(void)
{
    shipTexture = LoadTexture("assets/Ship.png");
    redShotTexture = LoadTexture("assets/RedShot.png");
    blueShotTexture = LoadTexture("assets/BlueShot.png");
}

void unloadAssets(void)
{
    UnloadTexture(blueShotTexture);
    UnloadTexture(redShotTexture);
    UnloadTexture(shipTexture);
}

void resetGame(void)
{
    pause = false, running = true;
    initShip(&enemy, gameWidth() / 2, 0, true, &shipTexture, &redShotTexture);
    initShip(&player, gameWidth() / 2, GetScreenHeight(), false, &shipTexture, &blueShotTexture);
}

void updateMenu(void)
{
    if (IsKeyPressed(KEY_P) && pause)
        pause = false;

    else if (IsKeyPressed(KEY_ENTER))
        resetGame();

    else if (IsKeyPressed(KEY_SPACE))
        IsWindowFullscreen()
            ? (ToggleFullscreen(), SetWindowSize(windowWidth, windowHeight))
            : (SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor())), ToggleFullscreen());
}

void drawMenu(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    char gameOverText[] = "Game Over";
    DrawText(gameOverText, gameWidth() / 2 - MeasureText(gameOverText, 24) / 2, gameHeight() - 24 * 3, 24, PURPLE);

    char replayText[] = "Press [Enter] to Replay";
    DrawText(replayText, gameWidth() / 2 - MeasureText(replayText, 24) / 2, gameHeight() - 24 * 1, 24, MAGENTA);

    char toggleFullscreenText[] = "Press [Space] to Toggle FullScreen";
    DrawText(toggleFullscreenText, gameWidth() / 2 - MeasureText(toggleFullscreenText, 24) / 2, gameHeight() - 24 * -1, 24, ORANGE);

    char togglePauseText[] = "Press [P] to Pause/Resume";
    DrawText(togglePauseText, gameWidth() / 2 - MeasureText(togglePauseText, 24) / 2, gameHeight() - 24 * -3, 24, BLUE);

    EndDrawing();
}

void updateGame(void)
{
    if (enemy.health <= 0 || player.health <= 0)
        pause = running = false;

    else if (IsKeyPressed(KEY_P))
        pause = running = true;

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

void drawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // center divider
    DrawLine(0, gameHeight(), gameWidth(), gameHeight(), BLUE);

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
