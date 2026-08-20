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

void draw_portal(Portal *portal1, Portal *portal2) {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        portal1->x = mouse.x;
        portal1->y = mouse.y;
        portal1->active = true;
        portal1->color = ORANGE;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        portal2->x = mouse.x;
        portal2->y = mouse.y;
        portal2->active = true;
        portal2->color = BLUE;
    }
    if (portal1->active) {
        DrawRectangle(portal1->x, portal1->y, portal1->width, portal1->height, portal1->color);
    }
    if (portal2->active) {
        DrawRectangle(portal2->x, portal2->y, portal2->width, portal2->height, portal2->color);
    }
}

void check_for_collision(Chell *chell, Portal *portal1, Portal *portal2) {
    Rectangle chell_rect = {chell->x, chell->y, chell->width, chell->height};
    Rectangle portal1_rect = {portal1->x, portal1->y, portal1->width, portal1->height};
    Rectangle portal2_rect = {portal2->x, portal2->y, portal2->width, portal2->height};

    if (CheckCollisionRecs(chell_rect, portal1_rect)) {
        chell->x = portal2->x + portal2->width;
        chell->y = portal2->y + portal2->height;
    }
    if (CheckCollisionRecs(chell_rect, portal2_rect)) {
        chell->x = portal1->x + portal1->width;
        chell->y = portal1->y + portal1->height;
    }

    chell->x = (chell->x + SCREEN_WIDTH) % SCREEN_WIDTH;
    chell->y = (chell->y + SCREEN_HEIGHT) % SCREEN_HEIGHT;
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