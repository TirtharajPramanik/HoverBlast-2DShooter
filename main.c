#include "game.h"

int main(void)
{
    InitWindow(windowWidth, windowHeight, windowTitle);
    InitAudioDevice();
    loadAssets();
    resetGame();

    running = false, SetTargetFPS(frameRate);
    while (!WindowShouldClose())
        running && !pause ? (updateGame(), drawGame())
                          : (updateMenu(), drawMenu());

    unloadAssets();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
