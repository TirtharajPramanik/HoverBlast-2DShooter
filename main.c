#include "game.h"

int main(void)
{
    loadAssets();
    resetGame();

    SetTargetFPS(frameRate);
    PlayMusicStream(backgroundMusic);

    gameover = true;
    while (!WindowShouldClose())
        gameover || pause ? (updateMenu(), helpDraw(drawMenu))
                          : (updateGame(), helpDraw(drawGame));

    unloadAssets();
    return 0;
}
