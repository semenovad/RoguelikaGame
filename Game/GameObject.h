//
// Created by daria on 22.02.2021.
//

#ifndef MAIN_GAMEOBJECT_H
#define MAIN_GAMEOBJECT_H

#include "Image.h"
#include "structure.h"
#include "vector"

struct GameObject {
    explicit GameObject(Point pos) : pos(pos), time(0), isPlayer(false){};

    void staticMove(float dt, std::vector<std::vector<char>> &tileData, gameState *state);
    void move(MovementDir dir, float dt, std::vector<std::vector<char>> &tileData, gameState *state);
    void setImage(const std::string &path) {
        Image *texture;
        texture = new Image(path);
        image.push_back(texture);
    }
    ~GameObject() {
        for (auto item : image) delete item;
    }

    bool isPlayer;
    Point pos = {0, 0};
    std::vector<Image*> image;
    double time;
    int dir = 0;

    MovementDir lastMove;
};

#endif //MAIN_GAMEOBJECT_H
