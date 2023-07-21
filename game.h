#pragma once
#include "ship.h"

#ifdef DEBUG
#include "debug.h"
#endif

Ship enemy, player;
bool running, pause;
Texture2D shipTexture, redShotTexture, blueShotTexture, backgroundTexture;

void loadAssets(void)
{
    shipTexture = LoadTexture("assets/Ship.png");
    redShotTexture = LoadTexture("assets/RedShot.png");
    blueShotTexture = LoadTexture("assets/BlueShot.png");
    backgroundTexture = LoadTexture("assets/Background.png");
}

void unloadAssets(void)
{
    UnloadTexture(backgroundTexture);
    UnloadTexture(blueShotTexture);
    UnloadTexture(redShotTexture);
    UnloadTexture(shipTexture);
}

void resetGame(void)
{
    pause = false, running = true;
    initShip(&enemy, gameWidth() / 2, 0, true, &shipTexture, &redShotTexture);
    initShip(&player, gameWidth() / 2, gameHeight(), false, &shipTexture, &blueShotTexture);
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

    // background tiles
    for (int y = 0; y < gameHeight(); y += bgSpan)
        for (int x = 0; x < gameWidth(); x += bgSpan)
            DrawTextureRec(backgroundTexture, (Rectangle){xMenuOffset, yMenuOffset, bgSpan, bgSpan}, (Vector2){x, y}, WHITE);

    char gameOverText[] = "Hover Blast";
    DrawText(gameOverText, gameWidth() / 2 - MeasureText(gameOverText, 24) / 2, arenaHeight() - 32 * 3, 32, VIOLET);

    char replayText[] = "Press [Enter] to Play/Replay";
    DrawText(replayText, gameWidth() / 2 - MeasureText(replayText, 24) / 2, arenaHeight() - 24 * 1, 24, LIME);

    char toggleFullscreenText[] = "Press [Space] to Toggle FullScreen";
    DrawText(toggleFullscreenText, gameWidth() / 2 - MeasureText(toggleFullscreenText, 24) / 2, arenaHeight() - 24 * -1, 24, RED);

    char togglePauseText[] = "Press [P] to Pause/Resume";
    DrawText(togglePauseText, gameWidth() / 2 - MeasureText(togglePauseText, 24) / 2, arenaHeight() - 24 * -3, 24, BLUE);

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

    // background tiles
    for (int y = 0; y < gameHeight(); y += bgSpan)
        for (int x = 0; x < gameWidth(); x += bgSpan)
            DrawTextureRec(backgroundTexture, (Rectangle){xGameOffset, yGameOffset, bgSpan, bgSpan}, (Vector2){x, y}, WHITE);

    drawShip(&enemy);
    drawShip(&player);

    for (int i = 0; i < maxShots; i++)
    {
        drawShot(&enemy.shots[i]);
        drawShot(&player.shots[i]);
    }

#ifdef DEBUG
    // center divider
    DrawLine(0, arenaHeight(), gameWidth(), arenaHeight(), BLUE);
    drawShotsSpeednPositions(2, enemy, player);
    drawShipnShotsBounds(2, enemy, player);
    drawShipSpeednHealth(2, enemy, player);
    drawShipPosition(2, enemy, player);
#endif

    EndDrawing();
}
