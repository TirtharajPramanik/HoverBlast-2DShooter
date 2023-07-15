#include <raylib.h>

const char windowTitle[] = "Dungeon Fighter";
const int windowWidth = 600, windowHeight = 600;
const int window_xCellCount = 12, window_yCellCount = 12;

const int ship_xCellCount = 1;
const float cellWidth = windowWidth / window_xCellCount;
int ship_xCellPos = window_xCellCount / 2, ship_yCellPos = 1;

void updateFrame(void);
void drawFrame(void);
void handleMovement(void);

int main(void)
{

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        updateFrame();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawFrame();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void updateFrame(void)
{
    handleMovement();
}

void drawFrame(void)
{
    DrawRectangle(ship_xCellPos * cellWidth, windowHeight - cellWidth - cellWidth * ship_yCellPos, cellWidth, cellWidth, MAROON);
}

void handleMovement(void)
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

    case KEY_S:
    case KEY_DOWN:
        if (ship_yCellPos > 0)
            ship_yCellPos--;
        break;

    case KEY_W:
    case KEY_UP:
        if (ship_yCellPos < window_yCellCount - 1)
            ship_yCellPos++;
        break;

    default:
        break;
    }
}