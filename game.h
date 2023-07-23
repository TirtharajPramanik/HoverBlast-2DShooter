#pragma once
#include "ship.h"

#ifdef DEBUG
#include "debug.h"
#endif

Ship enemy, player;
bool gameover, pause;

void resetGame(void)
{
    pause = false, gameover = !(player.alive && enemy.alive);
    initShip(&enemy, arenaWidth() / 2, 0, true);
    initShip(&player, arenaWidth() / 2, GetScreenHeight(), false);
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
            : (SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor())),
               ToggleFullscreen());
}

void drawMenu(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // background tiles
    for (int y = 0; y < GetScreenHeight(); y += bgSpan)
        for (int x = 0; x < GetScreenWidth(); x += bgSpan)
            DrawTextureRec(backgroundTexture, (Rectangle){xMenuOffset, yMenuOffset, bgSpan, bgSpan}, (Vector2){x, y}, WHITE);

    char gameOverText[] = "Hover Blast";
    DrawText(gameOverText, GetScreenWidth() / 2 - MeasureText(gameOverText, 24) / 2, arenaHeight() - 32 * 3, 32, VIOLET);

    char replayText[] = "Press [Enter] to Play/Replay";
    DrawText(replayText, GetScreenWidth() / 2 - MeasureText(replayText, 24) / 2, arenaHeight() - 24 * 1, 24, LIME);

    char toggleFullscreenText[] = "Press [Space] to Toggle FullScreen";
    DrawText(toggleFullscreenText, GetScreenWidth() / 2 - MeasureText(toggleFullscreenText, 24) / 2, arenaHeight() - 24 * -1, 24, RED);

    char togglePauseText[] = "Press [P] to Pause/Resume";
    DrawText(togglePauseText, GetScreenWidth() / 2 - MeasureText(togglePauseText, 24) / 2, arenaHeight() - 24 * -3, 24, BLUE);

    EndDrawing();
}

void updateGame(void)
{
    // game over logic
    if (enemy.health <= 0)
        enemy.alive = false;

    else if (player.health <= 0)
        player.alive = false;

    else if (IsKeyPressed(KEY_P))
        pause = true;

    // enemy logic
    if (enemy.alive)
    {
        moveShip(&enemy);
        for (int i = 0; i < maxShots; i++)
            if (checkShot(&player.shots[i], enemy.rect))
                player.score++, enemy.health--;
        shoot(&enemy);
    }
    else
        gameover = overBlast(&enemy);
    for (int i = 0; i < maxShots; i++)
        moveShot(&enemy.shots[i]);

    // player logic
    if (player.alive)
    {
        moveShip(&player);
        for (int i = 0; i < maxShots; i++)
            if (checkShot(&enemy.shots[i], player.rect))
                enemy.score++, player.health--;
        shoot(&player);
    }
    else
        gameover = overBlast(&player);
    for (int i = 0; i < maxShots; i++)
        moveShot(&player.shots[i]);
}

void drawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // background tiles
    for (int y = 0; y < GetScreenHeight(); y += bgSpan)
        for (int x = 0; x < arenaWidth(); x += bgSpan)
            DrawTextureRec(backgroundTexture, (Rectangle){xGameOffset, yGameOffset, bgSpan, bgSpan}, (Vector2){x, y}, WHITE);

    drawShipStats(&enemy);
    drawShipStats(&player);

    enemy.alive ? drawShip(&enemy) : drawBlast(&enemy);
    player.alive ? drawShip(&player) : drawBlast(&player);

    for (int i = 0; i < maxShots; i++)
    {
        drawShot(&enemy.shots[i]);
        drawShot(&player.shots[i]);
    }

#ifdef DEBUG
    // center divider
    DrawLine(0, arenaHeight(), arenaWidth(), arenaHeight(), BLUE);
    drawShotsSpeednPositions(2, enemy, player);
    drawShipnShotsBounds(2, enemy, player);
    drawShipSpeednHealth(2, enemy, player);
    drawShipPosition(2, enemy, player);
#endif

    EndDrawing();
}
