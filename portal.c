#include "portal.h"

Chell init_chell() {
    Chell chell;

    chell.x = SCREEN_WIDTH / 2;
    chell.y = SCREEN_HEIGHT / 2;

    chell.width = 20;
    chell.height = 50;

    return chell;
}

void draw_chell(Chell *chell) {
    DrawRectangle(chell->x, chell->y, chell->width, chell->height, RAYWHITE);
}