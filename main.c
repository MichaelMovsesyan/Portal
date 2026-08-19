#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "Raylib Test");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Raylib works!", 300, 200, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
