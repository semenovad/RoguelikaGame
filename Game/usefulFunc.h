//
// Created by daria on 27.02.2021.
//

#ifndef MAIN_USEFULFUNC_H
#define MAIN_USEFULFUNC_H

#include "structure.h"
#include "Image.h"
#include "GameLevel.h"

Point findArrayCoord(int x, int y);
Point findPicCoord(int i, int j);
void putTile(Image* screen, int i, int j, Image &tile);
void drawIntoScreen(Image* screen, Image* out, int i, int j);
void drawDoors(Image * screen, Image *openDoor, Image *closeDoor, const std::vector<Point> &vec,
               const std::vector<std::vector<char>> &tileData);
void changeDynamicObjectPos(std::vector<std::vector<char>> &tileData, int i1, int i2, int j1, int j2);
void changeDynamicObjectPos2(std::vector<std::vector<char>> &tileData, int i1, int j1, int i2, int j2, char obj);
void changeDoorAccess(std::vector<std::vector<char>> &tileData, int i, int j, int num);
Point isDoor(std::vector<std::vector<char>> &tileData, int i, int j, MovementDir dir);
void doorsChanges(std::vector<std::vector<char>> &tileData, Point &pos);
void printVec(std::vector<std::vector<char>> &tileData);
//vec3 rgbToHsv(const vec3 &rgb);
//vec3 hsvToRgb(const vec3 &hsv);
void RGBtoHSV(float fR, float fG, float fB, float &fH, float &fS, float &fV);
void HSVtoRGB(float &fR, float &fG, float &fB, float fH, float fS, float fV);
void brightManager(Image *screen, float bright);
void boxBlur(Image *screen);

#endif //MAIN_USEFULFUNC_H
