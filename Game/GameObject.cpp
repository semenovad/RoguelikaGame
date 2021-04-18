//
// Created by daria on 28.02.2021.
//
#include "structure.h"
#include "usefulFunc.h"
#include "GameObject.h"

/*
empty: ‘/‘
wall: ‘#’
floor: ‘.’
player: ‘@’
exit: ‘x’
door: ‘D’
 */

bool tileExpr(const std::vector<std::vector<char>> &tileData, int i, int j, gameState *state, bool isPlayer) {
    char tile = tileData[i][j];
    switch (tile) {
        case '@': {
            if (!isPlayer) {
                *state = gameState::LOSE;
                return true;
            }
        }
        case 'd': {
            if (!isPlayer) {
                return false;
            }
        }
        case '.': {
            return true;
        }
        case 'T':
        case 'D':
        case '#': {
            return false;
        }
        case '%': {
            *state = gameState::LOSE;
            return false;
        }
        case '/': {
            if (isPlayer) {
                *state = gameState::LOSE;
                return true;
            }
            else return false;
        }
        case 'x': {
            *state = gameState::WIN_LEVEL;
            return true;
        }
        default:
            break;
    }
    return false;
}

void GameObject::staticMove(float dt, std::vector<std::vector<char>> &tileData, gameState *state) {
    if (dir == 3 && !tileExpr(tileData, pos.y + 1, pos.x, state, isPlayer)) dir = 0;
    switch (dir) {
        case 0: {
            if (tileExpr(tileData, pos.y, pos.x + 1, state, isPlayer)) {
                dir = 0;
                changeDynamicObjectPos2(tileData, pos.y, pos.x, pos.y, pos.x + 1, '%');
                pos.x += 1;
                break;
            }
        }
        case 1: {
            if (tileExpr(tileData, pos.y - 1, pos.x, state, isPlayer)) {
                dir = 1;
                changeDynamicObjectPos2(tileData, pos.y, pos.x, pos.y - 1, pos.x, '%');
                pos.y -= 1;
                break;
            }
        }
        case 2: {
            if (tileExpr(tileData, pos.y, pos.x - 1, state, isPlayer)) {
                dir = 2;
                changeDynamicObjectPos2(tileData, pos.y, pos.x, pos.y, pos.x - 1, '%');
                pos.x -= 1;
                break;
            }
        }
        case 3: {
            if (tileExpr(tileData, pos.y + 1, pos.x, state, isPlayer)) {
                dir = 3;
                changeDynamicObjectPos2(tileData, pos.y, pos.x, pos.y + 1, pos.x, '%');
                pos.y += 1;
                break;
            }
        }
    }
}

void GameObject::move(MovementDir direct, float dt, std::vector<std::vector<char>> &tileData, gameState *state) {
    lastMove = direct;
    switch (direct) {
        case MovementDir::UP:
            dir = 0;
            if (tileExpr(tileData, pos.y + 1, pos.x, state, isPlayer)) {
                changeDynamicObjectPos(tileData, pos.y, pos.x, pos.y + 1, pos.x);
                pos.y += 1;
            }
            break;
        case MovementDir::DOWN:
            dir = 3;
            if (tileExpr(tileData, pos.y - 1, pos.x, state, isPlayer)) {
                changeDynamicObjectPos(tileData, pos.y, pos.x, pos.y - 1, pos.x);
                pos.y -= 1;
            }
            break;
        case MovementDir::LEFT:
            dir = 1;
            if (tileExpr(tileData, pos.y, pos.x - 1, state, isPlayer)) {
                changeDynamicObjectPos(tileData, pos.y, pos.x, pos.y, pos.x - 1);
                pos.x -= 1;
            }
            break;
        case MovementDir::RIGHT:
            dir = 2;
            if (tileExpr(tileData, pos.y, pos.x + 1, state, isPlayer)) {
                changeDynamicObjectPos(tileData, pos.y, pos.x, pos.y, pos.x + 1);
                pos.x += 1;
            }
            break;
        default:
            break;
    }
}