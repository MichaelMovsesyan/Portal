#include "portal.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal");
    SetTargetFPS(80);

    Chell chell = init_chell();
    Portal portal1 = init_portal();
    Portal portal2= init_portal();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        move_chell(&chell);
        apply_gravity(&chell);

        draw_chell(&chell);
        draw_portal(&portal1, &portal2);

        check_for_collision(&chell, &portal1, &portal2);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
