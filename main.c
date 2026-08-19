#include "portal.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal");

    Chell chell = init_chell();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        draw_chell(&chell);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
