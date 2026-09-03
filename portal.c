#include "portal.h"

// INITIALIZING STRUCTS

Chell init_chell() {
    Chell chell;

    chell.x = SCREEN_WIDTH / 2;
    chell.y = SCREEN_HEIGHT / 2;

    chell.width = 20;
    chell.height = 20;

    chell.velocity_x = 0;
    chell.velocity_y = 0;

    chell.old_x = chell.x;
    chell.old_y = chell.y;

    chell.grounded = false;

    return chell;
}

Portal init_portal() {
    Portal portal;

    portal.width = 40;
    portal.height = 10;
    portal.rect = (Rectangle){0, 0, portal.width, portal.height};

    portal.active = false;
    portal.side = SIDE_TOP;
    portal.color = ORANGE;
    return portal;
}

void set_portal_side(Portal *portal, PortalSide side) {

    portal->side = side;

    if (side == SIDE_TOP || side == SIDE_BOTTOM) {
        portal->rect.width = portal->width;
        portal->rect.height = portal->height;
    }
    else {
        portal->rect.width = portal->height;
        portal->rect.height = portal->width;
    }
}

// DRAWING FUNCTIONS

void draw_chell(GameState *state) {
    Chell* chell = &state->chell;
    DrawRectangle(chell->x, chell->y, chell->width, chell->height, RAYWHITE); 
}

void draw_portal_indicator(Portal *portal) {

    if (portal->side == SIDE_TOP) {

        DrawLine(
            portal->rect.x,
            portal->rect.y,
            portal->rect.x + portal->rect.width,
            portal->rect.y,
            WHITE
        );

    }
    else if (portal->side == SIDE_BOTTOM) {

        DrawLine(
            portal->rect.x,
            portal->rect.y + portal->rect.height,
            portal->rect.x + portal->rect.width,
            portal->rect.y + portal->rect.height,
            WHITE
        );

    }
    else if (portal->side == SIDE_LEFT) {

        DrawLine(
            portal->rect.x,
            portal->rect.y,
            portal->rect.x,
            portal->rect.y + portal->rect.height,
            WHITE
        );

    }
    else if (portal->side == SIDE_RIGHT) {

        DrawLine(
            portal->rect.x + portal->rect.width,
            portal->rect.y,
            portal->rect.x + portal->rect.width,
            portal->rect.y + portal->rect.height,
            WHITE
        );
    }
}

void draw_portal(GameState *state) {

    Portal *portal1 = &state->portal1;
    Portal *portal2 = &state->portal2;

    if (IsKeyPressed(KEY_ONE)) {
        set_portal_side(portal1, SIDE_TOP);
    }

    if (IsKeyPressed(KEY_TWO)) {
        set_portal_side(portal1, SIDE_BOTTOM);
    }

    if (IsKeyPressed(KEY_THREE)) {
        set_portal_side(portal1, SIDE_LEFT);
    }

    if (IsKeyPressed(KEY_FOUR)) {
        set_portal_side(portal1, SIDE_RIGHT);
    }
    if (IsKeyPressed(KEY_FIVE)) {
        set_portal_side(portal2, SIDE_TOP);
    }

    if (IsKeyPressed(KEY_SIX)) {
        set_portal_side(portal2, SIDE_BOTTOM);
    }

    if (IsKeyPressed(KEY_SEVEN)) {
        set_portal_side(portal2, SIDE_LEFT);
    }

    if (IsKeyPressed(KEY_EIGHT)) {
        set_portal_side(portal2, SIDE_RIGHT);
    }

    Vector2 mouse = GetMousePosition();

    // Middle click removes both portals
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        portal1->active = false;
        portal2->active = false;
    }

    // Left click places portal 1
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        portal1->rect.x = mouse.x;
        portal1->rect.y = mouse.y;
        portal1->active = true;
        portal1->color = ORANGE;
    }

    // Right click places portal 2
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        portal2->rect.x = mouse.x;
        portal2->rect.y = mouse.y;
        portal2->active = true;
        portal2->color = BLUE;
    }

    // Draw portals
    if (portal1->active) {
        DrawRectangleRec(portal1->rect, portal1->color);
        draw_portal_indicator(portal1);
    }

    if (portal2->active) {
        DrawRectangleRec(portal2->rect, portal2->color);
        draw_portal_indicator(portal2);
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

bool entered_portal(GameState *state, Portal *portal) {

    Chell *chell = &state->chell;

    if (portal->side == SIDE_TOP) {

        return (
            chell->old_y + chell->height <= portal->rect.y &&
            chell->y + chell->height >= portal->rect.y &&
            chell->x + chell->width > portal->rect.x &&
            chell->x < portal->rect.x + portal->rect.width
        );
    }

    if (portal->side == SIDE_BOTTOM) {

        return (
            chell->old_y >= portal->rect.y + portal->rect.height &&
            chell->y <= portal->rect.y + portal->rect.height &&
            chell->x + chell->width > portal->rect.x &&
            chell->x < portal->rect.x + portal->rect.width
        );
    }

    if (portal->side == SIDE_LEFT) {

        return (
            chell->old_x + chell->width <= portal->rect.x &&
            chell->x + chell->width >= portal->rect.x &&
            chell->y + chell->height > portal->rect.y &&
            chell->y < portal->rect.y + portal->rect.height
        );
    }

    if (portal->side == SIDE_RIGHT) {

        return (
            chell->old_x >= portal->rect.x + portal->rect.width &&
            chell->x <= portal->rect.x + portal->rect.width &&
            chell->y + chell->height > portal->rect.y &&
            chell->y < portal->rect.y + portal->rect.height
        );
    }

    return false;
}

Vector2 portal_normal(PortalSide side) {

    if (side == SIDE_TOP) {
        return (Vector2){0, -1};
    }

    if (side == SIDE_BOTTOM) {
        return (Vector2){0, 1};
    }

    if (side == SIDE_LEFT) {
        return (Vector2){-1, 0};
    }

    // SIDE_RIGHT
    return (Vector2){1, 0};
}

void transform_velocity(Chell *chell, Portal *entrance, Portal *exit) {

    double vx = chell->velocity_x;
    double vy = chell->velocity_y;

    // TOP/BOTTOM -> TOP/BOTTOM
    if ((entrance->side == SIDE_TOP || entrance->side == SIDE_BOTTOM) && (exit->side == SIDE_TOP || exit->side == SIDE_BOTTOM)) {
        chell->velocity_x = vx;

        if (entrance->side == exit->side) {
            // Top -> Top or Bottom -> Bottom
            chell->velocity_y = -vy;
        }
        else {
            // Top -> Bottom or Bottom -> Top
            chell->velocity_y = vy;
        }
    }

    // LEFT/RIGHT -> LEFT/RIGHT
    else if ((entrance->side == SIDE_LEFT || entrance->side == SIDE_RIGHT) && (exit->side == SIDE_LEFT || exit->side == SIDE_RIGHT)) {
        chell->velocity_y = vy;

        if (entrance->side == exit->side) {
            // Left -> Left or Right -> Right
            chell->velocity_x = -vx;
        }
        else {
            // Left -> Right or Right -> Left
            chell->velocity_x = vx;
        }
    }

    // TOP/BOTTOM -> LEFT/RIGHT
    else if (entrance->side == SIDE_TOP || entrance->side == SIDE_BOTTOM) {
        if (entrance->side == SIDE_TOP && exit->side == SIDE_LEFT) {

            // Down -> Left
            chell->velocity_x = -vy;
            chell->velocity_y = -vx;
        }

        else if (entrance->side == SIDE_TOP && exit->side == SIDE_RIGHT) {

            // Down -> Right
            chell->velocity_x = vy;
            chell->velocity_y = vx;
        }

        else if (entrance->side == SIDE_BOTTOM && exit->side == SIDE_LEFT) {

            // Up -> Left
            chell->velocity_x = vy;
            chell->velocity_y = vx;
        }

        else if (entrance->side == SIDE_BOTTOM && exit->side == SIDE_RIGHT) {

            // Up -> Right
            chell->velocity_x = -vy;
            chell->velocity_y = -vx;
        }
    }

    // LEFT/RIGHT -> TOP/BOTTOM
    else {

        if (entrance->side == SIDE_LEFT && exit->side == SIDE_TOP) {

            chell->velocity_x = vy;
            chell->velocity_y = -vx;
        }

        else if (entrance->side == SIDE_RIGHT && exit->side == SIDE_TOP) {

            chell->velocity_x = vy;
            chell->velocity_y = vx;
        }

        else if (entrance->side == SIDE_LEFT && exit->side == SIDE_BOTTOM) {

            chell->velocity_x = vy;
            chell->velocity_y = vx;
        }

        else if (entrance->side == SIDE_RIGHT && exit->side == SIDE_BOTTOM) {

            chell->velocity_x = vy;
            chell->velocity_y = -vx;
        }
    }
}

void teleport_chell(GameState *state, Portal *entrance, Portal *exit) {

    Chell *chell = &state->chell;

    Vector2 chell_center = {
        chell->x + chell->width / 2,
        chell->y + chell->height / 2
    };

    Vector2 entrance_center = {
        entrance->rect.x + entrance->rect.width / 2,
        entrance->rect.y + entrance->rect.height / 2
    };

    float tangent_offset;

    if (entrance->side == SIDE_TOP || entrance->side == SIDE_BOTTOM) {

        tangent_offset = chell_center.x - entrance_center.x;
    }
    else {
        tangent_offset = chell_center.y - entrance_center.y;
    }

    Vector2 exit_center = {
        exit->rect.x + exit->rect.width / 2,
        exit->rect.y + exit->rect.height / 2
    };

    Vector2 new_center = exit_center;

    if (exit->side == SIDE_TOP || exit->side == SIDE_BOTTOM) {
        new_center.x += tangent_offset;
    }
    else {
        new_center.y += tangent_offset;
    }

    Vector2 exit_normal = portal_normal(exit->side);

    float offset = 2.0f;

    new_center.x += exit_normal.x * (chell->width / 2 + offset);

    new_center.y += exit_normal.y * (chell->height / 2 + offset);

    chell->x = new_center.x - chell->width / 2;
    chell->y = new_center.y - chell->height / 2;

    // Transform Chell's velocity based on the
    // orientation of the two portals.
    transform_velocity(chell, entrance, exit);
}

void check_for_collision(GameState *state) {
    Chell *chell = &state->chell;
    Portal *portal1 = &state->portal1;
    Portal *portal2 = &state->portal2;

    if (portal1->active && portal2->active) {
        if (entered_portal(state, portal1)) {
            teleport_chell(state, portal1, portal2);
        }
        else if (entered_portal(state, portal2)) {
            teleport_chell(state, portal2, portal1);
        }
    }

    // Floor collision
    if (chell->y + chell->height >= SCREEN_HEIGHT) {
        chell->y = SCREEN_HEIGHT - chell->height;
        chell->velocity_y = 0;
        chell->grounded = true;
    }

    // Screen wrapping
    chell->x = (chell->x + SCREEN_WIDTH) % SCREEN_WIDTH;
    //chell->y = (chell->y + SCREEN_HEIGHT) % SCREEN_HEIGHT;
}

void move_chell(GameState *state) {
    Chell* chell = &state->chell;

    chell->old_x = chell->x;
    chell->old_y = chell->y;

    // Horizontal acceleration
    if (IsKeyDown(KEY_RIGHT)) {
        chell->velocity_x += 0.1;

        if (chell->velocity_x > 3) {
            chell->velocity_x = 3;
        }
    }

    if (IsKeyDown(KEY_LEFT)) {
        chell->velocity_x -= 0.1;

        if (chell->velocity_x < -3) {
            chell->velocity_x = -3;
        }
    }

    // Apply horizontal velocity
    chell->x += chell->velocity_x;

    // Jump
    if (IsKeyPressed(KEY_SPACE) && chell->grounded) {
        chell->velocity_y = -5;
        chell->grounded = false;
    }

    chell->x = (chell->x + SCREEN_WIDTH) % SCREEN_WIDTH;
    chell->y = (chell->y + SCREEN_HEIGHT) % SCREEN_HEIGHT;
}

void apply_gravity(GameState *state) {
    Chell* chell = &state->chell;
    chell->velocity_y += 0.1;
    chell->y += chell->velocity_y;
}