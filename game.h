#pragma once
#include "ship.h"

#ifdef DEBUG
#include "debug.h"
#endif

Ship enemy, player;
Rectangle inputTextRect;
bool gameover, pause, mouseOnText;
char nameInput[maxInputChars + 1] = "\0"; // Name is not reset
int botFrameDelay, inputLetterCount, cursorBlinkDelay;

void resetGame(void)
{
    pause = false, gameover = !(player.alive && enemy.alive), mouseOnText = false;
    botFrameDelay = 0, inputLetterCount = 0, botFrameDelay = 0, cursorBlinkDelay = 0;
    initShip(&enemy, arenaWidth() / 2, 0, true);
    initShip(&player, arenaWidth() / 2, GetScreenHeight(), false);
}

void drawShipStats(Ship *ship)
{
    drawStats(ship->isEnemy ? "Bot" : ((nameInput[0] == '\0') ? "Player" : nameInput), ship->score, ship->health,
              ship->isEnemy ? fontSize : GetScreenHeight() - fontSize * 4, fontSize, ship->isEnemy ? RED : VIOLET);
}

void updateTextInput()
{
    cursorBlinkDelay = mouseOnText ? cursorBlinkDelay + 1 : 0;
    mouseOnText = CheckCollisionPointRec(GetMousePosition(), inputTextRect);
    if (mouseOnText)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        // Check if more characters have been pressed on the same frame
        while (key > 0)
        { // only allow keys in range [33..125]
            if ((key >= 33) && (key <= 125) && (inputLetterCount < maxInputChars))
            {
                nameInput[inputLetterCount] = (char)key;
                nameInput[inputLetterCount + 1] = '\0'; // add null terminator at the end of the string
                inputLetterCount++;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            inputLetterCount--;
            if (inputLetterCount < 0)
                inputLetterCount = 0;
            nameInput[inputLetterCount] = '\0';
        }
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void drawTextInput(void)
{
    DrawRectangleRec(inputTextRect, LIGHTGRAY);
    DrawRectangleLines(inputTextRect.x, inputTextRect.y, inputTextRect.width, inputTextRect.height, mouseOnText ? RED : DARKGRAY);

    DrawText(nameInput, inputTextRect.x + 5, inputTextRect.y + 8, fontSize, MAROON);
    DrawText(TextFormat("INPUT CHARS: %i/%i", inputLetterCount, maxInputChars),
             inputTextRect.x, inputTextRect.y + inputTextRect.height + 8, fontSize / 1.5, DARKGRAY);
    // draw blinking underscore char
    if (mouseOnText && inputLetterCount < maxInputChars)
        if (((cursorBlinkDelay / 20) % 2) == 0)
            DrawText("_", inputTextRect.x + 8 + MeasureText(nameInput, fontSize), inputTextRect.y + 12, fontSize, MAROON);
}

void updateMenu(void)
{
    if (IsKeyPressed(KEY_TAB) && pause)
        pause = false;
    else if (IsKeyPressed(KEY_ENTER))
        resetGame();
    else if (IsKeyPressed(KEY_SPACE))
        IsWindowFullscreen()
            ? (ToggleFullscreen(), SetWindowSize(windowWidth, windowHeight))
            : (SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor())),
               ToggleFullscreen());
    updateTextInput();
}

void drawMenu(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // background tiles
    for (int y = 0; y < GetScreenHeight(); y += bgSpan)
        for (int x = 0; x < GetScreenWidth(); x += bgSpan)
            DrawTextureRec(backgroundTexture, (Rectangle){xMenuOffset, yMenuOffset, bgSpan, bgSpan}, (Vector2){x, y}, WHITE);

    char gameTitleText[] = "Hover Blast";
    DrawText(gameTitleText, GetScreenWidth() / 2 - MeasureText(gameTitleText, 32) / 2, arenaHeight() - 32 * 6, 32, VIOLET);

    char nameInputText[] = "Player Name: ";
    DrawText(nameInputText, GetScreenWidth() / 2 - MeasureText(nameInputText, fontSize), arenaHeight() - 32 * 3, fontSize, GRAY);

    inputTextRect = (Rectangle){(GetScreenWidth() / 2) - (225 / 2), arenaHeight() - 32 * 2, 225, 32};
    drawTextInput();

    char replayText[] = "Press [Enter] to Play/Replay";
    DrawText(replayText, GetScreenWidth() / 2 - MeasureText(replayText, fontSize) / 2, arenaHeight() - fontSize * -1, fontSize, LIME);

    char toggleFullscreenText[] = "Press [Space] to Toggle FullScreen";
    DrawText(toggleFullscreenText, GetScreenWidth() / 2 - MeasureText(toggleFullscreenText, fontSize) / 2, arenaHeight() - fontSize * -3, fontSize, RED);

    char togglePauseText[] = "Press [Tab] to Pause/Resume";
    DrawText(togglePauseText, GetScreenWidth() / 2 - MeasureText(togglePauseText, fontSize) / 2, arenaHeight() - fontSize * -5, fontSize, BLUE);

    char inGameKeysText[] = "In Game: [W A S D] to Move & [Space/F] to Shoot";
    DrawText(inGameKeysText, GetScreenWidth() / 2 - MeasureText(inGameKeysText, fontSize) / 2, arenaHeight() - fontSize * -7, fontSize, BLACK);

    EndDrawing();
}

void calculateBotMovement(Ship *enemy, Ship *player)
{
    // avoid bullet hits (intentinally, does not move out of the way of bullets, instead moves to the direction where is more space)
    botFrameDelay++;
    if (botFrameDelay > botMaxFrameDelay)
        botFrameDelay = 0, enemy->direc = NONE;
    else if (enemy->direc == UP || enemy->direc == DOWN)
        enemy->direc = NONE;
    else
        for (int i = 0; i < maxShots; i++)
            if (player->shots[i].active && player->shots[i].pos.y < arenaHeight())
                enemy->direc = enemy->rect.x < arenaWidth() / 2 ? RIGHT : LEFT;

    // follow player when too far
    if (player->rect.x - enemy->rect.x > botFollowThresh())
        enemy->direc = RIGHT;
    else if (player->rect.x - enemy->rect.x < -botFollowThresh())
        enemy->direc = LEFT;

    // randomly move up & down
    if (GetRandomValue(0, botVerticalMoveProba) == 0)
        enemy->direc = GetRandomValue(0, 1) ? UP : DOWN;
}

void updateGame(void)
{
    // game over logic
    if (enemy.health <= 0)
        enemy.alive = false;

    else if (player.health <= 0)
        player.alive = false;

    else if (IsKeyPressed(KEY_TAB))
        pause = true;

    calculateBotMovement(&enemy, &player);

    // enemy logic
    if (enemy.alive)
    {
        handleMovement(&enemy);
        for (int i = 0; i < maxShots; i++)
            if (checkShot(&player.shots[i], enemy.rect))
                PlaySound(getShotSound), player.score++, enemy.health--;
        shoot(&enemy, (enemy.rect.x + enemy.rect.width) >= player.rect.x && // shoot when player in sight
                          enemy.rect.x <= (player.rect.x + player.rect.width));
    }
    else
        gameover = overBlast(&enemy);

    // player logic
    if (player.alive)
    {
        handleMovement(&player);
        for (int i = 0; i < maxShots; i++)
            if (checkShot(&enemy.shots[i], player.rect))
                PlaySound(getShotSound), enemy.score++, player.health--;
        shoot(&player, IsKeyDown(KEY_F) || IsKeyDown(KEY_SPACE));
    }
    else
        gameover = overBlast(&player);

    for (int i = 0; i < maxShots; i++)
        moveShot(&enemy.shots[i]),
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
        drawShot(&enemy.shots[i]),
            drawShot(&player.shots[i]);

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
