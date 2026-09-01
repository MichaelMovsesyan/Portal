#include "portal.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal");
    SetTargetFPS(80);

    GameState state = (GameState){
        .chell = init_chell(),
        .portal1 = init_portal(),
        .portal2 = init_portal(),
    };

    // Chell chell = init_chell();
    // Portal portal1 = init_portal();
    // Portal portal2= init_portal();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        move_chell(&state);
        apply_gravity(&state);

        draw_chell(&state);
        draw_portal(&state);

        check_for_collision(&state);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
