#ifndef PORTAL_H
#define PORTAL_H

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 450

typedef struct {
    int width, height;
    int x, y;
    double velocity_y;
    double velocity_x;
    bool grounded;
    double old_x, old_y;
} Chell;

typedef enum {
    SIDE_TOP,
    SIDE_BOTTOM,
    SIDE_LEFT,
    SIDE_RIGHT
} PortalSide;

typedef struct {
    bool active;
    int width, height;
    PortalSide side;
    Color color;
    Rectangle rect;
} Portal;

typedef struct {
    Chell chell;
    Portal portal1;
    Portal portal2;
} GameState;

Chell init_chell();

Portal init_portal();

void draw_chell(GameState *state);

void draw_portal_indicator(Portal *portal);

void draw_portal(GameState *state);

int new_x(int chell_x, int portal_x);

int new_y(int chell_y, int portal_y);

bool entered_portal(GameState *state, Portal *portal);

Vector2 portal_normal(PortalSide side);

void transform_velocity(Chell *chell, Portal *entrance, Portal *exit);

void teleport_chell(GameState *state, Portal *entrance, Portal *exit);

void check_for_collision(GameState* state);

void move_chell(GameState *state);

void apply_gravity(GameState *state);

#endif