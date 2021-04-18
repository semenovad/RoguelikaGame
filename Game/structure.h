//
// Created by daria on 25.02.2021.
//

#ifndef MAIN_STRUCTURE_H
#define MAIN_STRUCTURE_H

#include <GLFW/glfw3.h>

constexpr int tileSize = 24;
constexpr GLsizei WINDOW_WIDTH = 960, WINDOW_HEIGHT = 960;

struct vec3 {
    double r;
    double g;
    double b;
};

struct Point {
    int x;
    int y;
};

enum gameState {
    ACTIVE,
    LOSE,
    WIN_LEVEL,
    BLUR,
    BRIGHT_OFF,
    BRIGHT_ON,
};

enum class MovementDir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};


#endif //MAIN_STRUCTURE_H
