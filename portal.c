#include "portal.h"

// INITIALIZING STRUCTS

Chell init_chell() {
    Chell chell;

    chell.x = SCREEN_WIDTH / 2;
    chell.y = SCREEN_HEIGHT / 2;

    chell.width = 20;
    chell.height = 20;

    chell.velocity_y = 0;
    chell.grounded = false;

    return chell;
}

Portal init_portal() {
    Portal portal;
    portal.width = 20;
    portal.height = 40;
    portal.active = false;
    return portal;
}

// DRAWING FUNCTIONS

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

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        portal1->active = false;
        portal2->active = false;
    }
}

// MOVEMENT FUNCTIONS

int new_x(int chell_x, int portal_x) {
    int new_x = chell_x - portal_x;
    
    return new_x * -1;
}

int new_y(int chell_y, int portal_y) {
    int new_y = chell_y - portal_y;

    return new_y;
}

void check_for_collision(Chell *chell, Portal *portal1, Portal *portal2)
{
    Rectangle chell_rect = {
        chell->x,
        chell->y,
        chell->width,
        chell->height
    };

    Rectangle portal1_rect = {
        portal1->x,
        portal1->y,
        portal1->width,
        portal1->height
    };

    Rectangle portal2_rect = {
        portal2->x,
        portal2->y,
        portal2->width,
        portal2->height
    };


    if (portal1->active && portal2->active) {

        // PORTAL 1

        if (CheckCollisionRecs(chell_rect, portal1_rect)) {

            // Chell is touching the top
            if (chell->y + chell->height <= portal1->y + 1) {
                chell->y = portal1->y - chell->height;
            }

            // Chell is touching the bottom
            else if (chell->y >= portal1->y + portal1->height - 1) {
                chell->y = portal1->y + portal1->height;
            }

            // Otherwise, teleport
            else {
                chell->x = portal2->x + new_x(chell->x, portal1->x);
                chell->y = portal2->y + new_y(chell->y, portal1->y);
            }
        }


        // PORTAL 2

        if (CheckCollisionRecs(chell_rect, portal2_rect)) {

            // Chell is touching the top
            if (chell->y + chell->height <= portal2->y + 1) {
                chell->y = portal2->y - chell->height;
            }

            // Chell is touching the bottom
            else if (chell->y >= portal2->y + portal2->height - 1) {
                chell->y = portal2->y + portal2->height;
            }

            // Otherwise, teleport
            else {
                chell->x = portal1->x + new_x(chell->x, portal2->x);
                chell->y = portal1->y + new_y(chell->y, portal2->y);
            }
        }
    }

    if (chell->y + chell->height >= SCREEN_HEIGHT) {
        chell->y = SCREEN_HEIGHT - chell->height;
        chell->velocity_y = 0;
        chell->grounded = true;
    }

    chell->x = (chell->x + SCREEN_WIDTH) % SCREEN_WIDTH;
    chell->y = (chell->y + SCREEN_HEIGHT) % SCREEN_HEIGHT;
}

void move_chell(Chell *chell) {
    if (IsKeyDown(KEY_RIGHT)) {
        chell->x += 2;
    }
    if (IsKeyDown(KEY_LEFT)) {
        chell->x -= 2;
    }
    if (IsKeyDown(KEY_UP)) {
        chell->y -= 2;
    }
    if (IsKeyDown(KEY_DOWN)) {
        chell->y += 2;
    }
    if (IsKeyPressed(KEY_SPACE) && chell->grounded) {
        chell->velocity_y = -5;
        chell->grounded = false;
    }
    chell->x = (chell->x + SCREEN_WIDTH) % SCREEN_WIDTH;
    chell->y = (chell->y + SCREEN_HEIGHT) % SCREEN_HEIGHT;
}

void apply_gravity(Chell *chell) {
    chell->velocity_y += 0.1;

    if (chell->velocity_y > 5) {
        chell->velocity_y = 5;
    }

    chell->y += chell->velocity_y;
}