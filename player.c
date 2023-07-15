#include <raylib.h>

const char windowTitle[] = "Dungeon Fighter";

const int windowWidth = 600;
const int windowHeight = 600;
const int window_xCellCount = 12;

const int ship_xCellCount = 1;
int ship_xCellPos = window_xCellCount / 2;
const float cellWidth = windowWidth / window_xCellCount;

void update(void);

int main(void)
{

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        update();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(ship_xCellPos * cellWidth, windowHeight - cellWidth, cellWidth, cellWidth, MAROON);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void update(void)
{
    switch (GetKeyPressed())
    {
    case KEY_A:
    case KEY_LEFT:
        if (ship_xCellPos > 0)
            ship_xCellPos--;
        break;

    case KEY_D:
    case KEY_RIGHT:
        if (ship_xCellPos < window_xCellCount - 1)
            ship_xCellPos++;
        break;

    default:
        break;
    }
}