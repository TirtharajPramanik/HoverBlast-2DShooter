#include <raylib.h>

#define WIDTH 640
#define HEIGHT 460

int main(void)
{
    const char text[] = "Welcome to Game Window";

    InitWindow(WIDTH, HEIGHT, "Game Window");
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(text, WIDTH / 2 - 8 * (int)sizeof(text), HEIGHT / 2 - 32, 32, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}