#include "game.h"

int main(void)
{
    InitWindow(windowWidth, windowHeight, windowTitle);
    InitAudioDevice();
    loadAssets();
    resetGame();

    gameover = true, SetTargetFPS(frameRate);
    while (!WindowShouldClose())
        gameover || pause ? (updateMenu(), drawMenu())
                          : (updateGame(), drawGame());

    unloadAssets();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
