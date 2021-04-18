//
// Created by daria on 22.02.2021.
//
#include "GameLevel.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "usefulFunc.h"

/*
empty: ‘/‘
wall: ‘#’
floor: ‘.’
player: ‘@’
exit: ‘x’
door: ‘D’
 */

std::vector<std::string> emptySpaceVec{"../resources/emptySpace1.png", "../resources/emptySpace2.png"};
std::vector<std::string> wallVec{"../resources/wall1.png", "../resources/wall2.png"};
std::vector<std::string> floorTileVec{"../resources/floorTile1.png", "../resources/floorTile2.png"};
std::vector<std::string> exitTileVec{"../resources/exit.png", "../resources/exit.png"};

char GameLevel::getChar(int i, int j) {
    return tileData[i][j];
}

void GameLevel::makeLevelMap() {
    Image emptySpace(emptySpaceVec[level]);
    Image wall(wallVec[level]);
    Image floorTile(floorTileVec[level]);
    Image exitTile(exitTileVec[level]);

    for (int i = 0; i < size.x; ++i) {
        for (int j = 0; j < size.y; ++j) {
            switch (tileData[i][j]) {
                case '/': {
                    putTile(levelMap, i, j, emptySpace);
                    break;
                }
                case '#': {
                    putTile(levelMap, i, j, wall);
                    break;
                }
                case 'T':
                case 'D':
                case '@':
                case '%':
                case '.': {
                    putTile(levelMap, i, j, floorTile);
                    break;
                }
                case 'x': {
                    putTile(levelMap, i, j, exitTile);
                    break;
                }
            }
        }
    }
}

void GameLevel::Load(const char *file, Point s, unsigned int l) {
    levelMap = new Image(WINDOW_WIDTH, WINDOW_HEIGHT, 4);

    size.x = s.x;
    size.y = s.y;
    level = l;

    std::string tileCode;
    std::string line;
    std::ifstream fin(file);
    int i, j = 0;

    bool isDoor = false;
    if (fin) {
        while (std::getline(fin, line)) {
            std::istringstream sstream(line);
            std::vector<char> row;
            sstream >> tileCode;
            i = 0;
            for (auto item : tileCode) {
                if (item == '/') {
                    emptyPos.push_back({i, j});
                }
                else if (item == 'T') {
                    torchPos.push_back({i, j});
                }
                else if (item == '%') {
                    evilStartPos.push_back({i, j});
                }
                else if (item == '@') {
                    playerStartPos = {i, j};
                }
                else if (item == 'D') {
                    doorPos.push_back({i, j});
                }
                row.push_back(item);
                ++i;
            }
            ++j;
            tileData.push_back(row);
        }
    }
    makeLevelMap();
}




