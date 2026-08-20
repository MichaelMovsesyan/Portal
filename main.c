#include "portal.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal");

    Chell chell = init_chell();
    Portal portal1 = init_portal();
    Portal portal2= init_portal();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        move_chell(&chell);

        draw_chell(&chell);
        draw_portal(&portal1, &portal2);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
