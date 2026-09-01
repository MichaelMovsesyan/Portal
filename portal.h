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
    bool grounded;
    double old_y;
} Chell;

typedef struct {
    int x, y;
    int width, height;
    bool active;
    Color color;
} Portal;

typedef struct {
    Chell chell;
    Portal portal1;
    Portal portal2;
} GameState;

Chell init_chell();

Portal init_portal();

void draw_chell(GameState *state);

void draw_portal(GameState *state);

int new_x(int chell_x, int portal_x);

int new_y(int chell_y, int portal_y);

void update_rectangles(Chell *chell, Portal *portal1, Portal *portal2);

void check_for_collision(GameState* state);

void move_chell(GameState *state);

void apply_gravity(GameState *state);

#endif