#ifndef PORTAL_H
#define PORTAL_H

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    int width, height;
    int x, y;
} Chell;

Chell init_chell();

void draw_chell(Chell* chell);

#endif