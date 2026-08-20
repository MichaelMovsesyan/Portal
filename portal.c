#include "portal.h"

Chell init_chell() {
    Chell chell;

    chell.x = SCREEN_WIDTH / 2;
    chell.y = SCREEN_HEIGHT / 2;

    chell.width = 20;
    chell.height = 20;

    return chell;
}

Portal init_portal() {
    Portal portal;
    portal.width = 20;
    portal.height = 20;
    return portal;
}

void draw_chell(Chell *chell) {
    DrawRectangle(chell->x, chell->y, chell->width, chell->height, RAYWHITE);
}

void draw_portal(Portal *portal) {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        portal->x = mouse.x;
        portal->y = mouse.y;
        portal->active = true;
        portal->color = ORANGE;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        portal->x = mouse.x;
        portal->y = mouse.y;
        portal->active = true;
        portal->color = BLUE;
    }
    if (portal->active) {
        DrawRectangle(portal->x, portal->y, portal->width, portal->height, portal->color);
    }
}

void move_chell(Chell *chell) {
    if (IsKeyDown(KEY_RIGHT)) {
        chell->x += 1;
    }
    if (IsKeyDown(KEY_LEFT)) {
        chell->x -= 1;
    }
    if (IsKeyDown(KEY_UP)) {
        chell->y -= 1;
    }
    if (IsKeyDown(KEY_DOWN)) {
        chell->y += 1;
    }
    chell->x = (chell->x + SCREEN_WIDTH) % SCREEN_WIDTH;
    chell->y = (chell->y + SCREEN_HEIGHT) % SCREEN_HEIGHT;
}