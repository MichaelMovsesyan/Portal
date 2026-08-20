#include "portal.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal");

    Chell chell = init_chell();
    Portal portal = init_portal();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        move_chell(&chell);

        draw_chell(&chell);
        draw_portal(&portal);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
