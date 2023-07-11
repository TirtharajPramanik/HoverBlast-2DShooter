#include <raylib.h>

#define WIDTH 800
#define HEIGHT 800

void move_ball(Vector2 *ballPos, int speed);

int main(void)
{
    Vector2 ballPos = {WIDTH / 2, HEIGHT / 2};
    int speed = 300;

    InitWindow(WIDTH, HEIGHT, "Game Window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        move_ball(&ballPos, speed);

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircle(ballPos.x, ballPos.y, 10, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void move_ball(Vector2 *ballPos, int speed)
{
    short kw, ks, ka, kd;
    kw = ks = ka = kd = 0;
    if (IsKeyDown(KEY_W))
        kw = 1;
    if (IsKeyDown(KEY_S))
        ks = 1;
    if (IsKeyDown(KEY_A))
        ka = 1;
    if (IsKeyDown(KEY_D))
        kd = 1;
    const int p = kw + ks + ka + kd;

    if (p)
    {
        float delta = speed * GetFrameTime() / p;
        if (kw)
            ballPos->y -= delta;
        if (ks)
            ballPos->y += delta;
        if (ka)
            ballPos->x -= delta;
        if (kd)
            ballPos->x += delta;
    }
}

// void move_ball(Vector2 *ballPos, int speed)
// {
//     float delta = speed * GetFrameTime();
//     if (IsKeyDown(KEY_W))
//         ballPos->y -= delta;
//     if (IsKeyDown(KEY_S))
//         ballPos->y += delta;
//     if (IsKeyDown(KEY_A))
//         ballPos->x -= delta;
//     if (IsKeyDown(KEY_D))
//         ballPos->x += delta;
// }