#include "game.h"

int main(void)
{
    InitWindow(windowWidth, windowHeight, windowTitle);

    loadAssets();
    resetGame();
    SetTargetFPS(frameRate);

    running = false;
    while (!WindowShouldClose())
        running && !pause
            ? (updateGame(), drawGame())
            : (updateMenu(), drawMenu());

    unloadAssets();
    CloseWindow();
    return 0;
}
