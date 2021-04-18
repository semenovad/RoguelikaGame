//
// Created by daria on 22.02.2021.
//

#ifndef MAIN_GAMELEVEL_H
#define MAIN_GAMELEVEL_H

#include "structure.h"
#include "GameObject.h"
#include "Image.h"
#include <vector>

/*
empty: ‘/‘
wall: ‘#’
floor: ‘.’
player: ‘@’
exit: ‘x’
door: ‘D’
 */

class GameLevel {
public:
    GameLevel() {};
    void Load (const char *file, Point size, unsigned int level);
    char getChar(int i, int j);

    Point size;
    Image *levelMap;
    unsigned int level;
    std::vector<std::vector<char>> tileData;
    std::vector<Point> doorPos;
    std::vector<Point> emptyPos;
    std::vector<Point> evilStartPos;
    std::vector<Point> torchPos;

    Point playerStartPos;
    std::vector<GameObject> dynamicObj;

private:
    void makeLevelMap();
};

#endif //MAIN_GAMELEVEL_H
