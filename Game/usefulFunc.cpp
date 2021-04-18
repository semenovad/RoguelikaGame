//
// Created by daria on 27.02.2021.
//

#include "usefulFunc.h"
#include <stdio.h>
#include <cmath>

Point findArrayCoord(Point &pos) {
    return {pos.x / tileSize, pos.y / tileSize};
};

Point findPicCoord(int i, int j) {
    return {i * tileSize, j * tileSize};
};

void putTile(Image *screen, int i, int j, Image &tile) {
    Point coord = findPicCoord(j, i);
    for (int y = coord.y; y < coord.y + tileSize; ++y) {
        for (int x = coord.x; x < coord.x + tileSize; ++x) {
            Pixel curPixel = tile.GetPixel(x - coord.x, y - coord.y);
            if (curPixel.a != 0) {
                screen->PutPixel(x, y, curPixel);
            }
        }
    }
};

void drawIntoScreen(Image *screen, Image *out, int i, int j) {
    Point coord = findPicCoord(i, j);;
    for (int y = coord.y; y < coord.y + out->Height(); ++y) {
        for (int x = coord.x; x < coord.x + out->Width(); ++x) {
            Pixel curPixel = out->GetPixel(x - coord.x, y - coord.y);
            if (curPixel.a != 0) {
                screen->PutPixel(x, y, curPixel);
            }
        }
    }
};

void drawDoors(Image *screen, Image *openDoor, Image *closeDoor, const std::vector<Point> &vec,
               const std::vector<std::vector<char>> &tileData) {
    for (auto &item : vec) {
        if (tileData[item.y][item.x] == 'd') {
            drawIntoScreen(screen, openDoor, int(item.x), int(item.y));
        } else if (tileData[item.y][item.x] == 'D') {
            drawIntoScreen(screen, closeDoor, int(item.x), int(item.y));
        }
    }
};

bool isLittleD;

void changeDynamicObjectPos(std::vector<std::vector<char>> &tileData, int i1, int j1, int i2, int j2) {
    if (isLittleD) tileData[i1][j1] = 'd';
    else tileData[i1][j1] = '.';
    if (tileData[i2][j2] == 'd') isLittleD = true;
    else isLittleD = false;
    tileData[i2][j2] = '@';
}

bool isLittleD2;

void changeDynamicObjectPos2(std::vector<std::vector<char>> &tileData, int i1, int j1, int i2, int j2, char obj) {
    if (isLittleD2) tileData[i1][j1] = 'd';
    else tileData[i1][j1] = '.';
    if (tileData[i2][j2] == 'd') isLittleD2 = true;
    else isLittleD2 = false;
    tileData[i2][j2] = obj;
}

void changeDoorAccess(std::vector<std::vector<char>> &tileData, int i, int j, int num) {
    if (tileData[i][j] == 'd') tileData[i][j] = 'D';
    else tileData[i][j] = 'd';
}

Point isDoor(std::vector<std::vector<char>> &tileData, int i, int j, MovementDir dir) {
    switch (dir) {
        case MovementDir::UP:
            j++;
            if (j >= 0 && j < 40 && (tileData[j][i] == 'D' || tileData[j][i] == 'd')) return {i, j};
            break;
        case MovementDir::DOWN:
            j--;
            if (j >= 0 && j < 40 && (tileData[j][i] == 'D' || tileData[j][i] == 'd')) return {i, j};
            break;
        case MovementDir::LEFT:
            i--;
            if (i >= 0 && i < 40 && (tileData[j][i] == 'D' || tileData[j][i] == 'd')) return {i, j};
            break;
        case MovementDir::RIGHT:
            i++;
            if (i >= 0 && i < 40 && (tileData[j][i] == 'D' || tileData[j][i] == 'd')) return {i, j};
            break;
        default:
            break;
    }
    return {-1, -1};
}

void doorsChanges(std::vector<std::vector<char>> &tileData, Point &pos) {
    changeDoorAccess(tileData, pos.y, pos.x, tileData[pos.x][pos.y]);
}

void printVec(std::vector<std::vector<char>> &tileData) {
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 40; ++j) {
            printf("%c ", tileData[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
vec3 rgbToHsv(const vec3 &rgb) {
    double mx = std::max(std::max(rgb.r, rgb.g), rgb.b);
    double mn = std::min(std::min(rgb.r, rgb.g), rgb.b);
    double d = mx - mn;
    if (mx == 0) {
        return vec3{0, 0, 0};
    }
    double v = mx;
    double s = d / mx;
    double h;
    if (mx == rgb.r) {
        h = 60 * (rgb.g - rgb.b) / d;
    } else if (mx == rgb.g) {
        h = 60 * (rgb.b - rgb.r) / d + 120;
    } else {
        h = 60 * (rgb.r - rgb.g) + 240;
    }
    return vec3{h, s, v};
}

vec3 hsvToRgb(const vec3 &hsv) {
    double v = hsv.b;
    if (hsv.g < 0.001) {
        return vec3{hsv.r, hsv.g, hsv.b};
    }
    double h = hsv.r * 6.0;
    double fi = floor(h);
    int i = int(fi);
    float f = h - fi;
    float p = hsv.b * (1.0 - hsv.g);
    float q = hsv.b * (1.0 - hsv.g * f);
    float t = hsv.b * (1.0 - hsv.g * (1.0 - f));
    if (i == 0) {
        return vec3{v, t, p};
    } else if (i == 1) {
        return vec3{q, v, p};
    } else if (i == 2) {
        return vec3{p, v, t};
    } else if (i == 3) {
        return vec3{p, q, v};
    } else if (i == 4) {
        return vec3{t, p, v};
    } else {
        return vec3{v, p, q};
    }
}

void brightManager(Image *screen, float bright) {
    vec3 rgb, hsv;
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        for (int j = 0; j < WINDOW_WIDTH; j++) {
            Pixel pix = screen->GetPixel(i, j);
            rgb.r = pix.r / 255.0;
            rgb.g = pix.g / 255.0;
            rgb.b = pix.b / 255.0;

            hsv = rgbToHsv(rgb);
            hsv.b *= bright;
            rgb = hsvToRgb(hsv);

            Pixel blend = {(uint8_t) (rgb.r * 255.0), (uint8_t) (rgb.g * 255.0), (uint8_t) (rgb.b * 255.0), 255};
            screen->PutPixel(i, j, blend);
        }
    }
}
*/

void RGBtoHSV(float fR, float fG, float fB, float &fH, float &fS, float &fV) {
    float fCMax = std::max(std::max(fR, fG), fB);
    float fCMin = std::min(std::min(fR, fG), fB);
    float fDelta = fCMax - fCMin;

    if (fDelta > 0) {
        if (fCMax == fR) {
            fH = 60 * (fmod(((fG - fB) / fDelta), 6));
        } else if (fCMax == fG) {
            fH = 60 * (((fB - fR) / fDelta) + 2);
        } else if (fCMax == fB) {
            fH = 60 * (((fR - fG) / fDelta) + 4);
        }

        if (fCMax > 0) {
            fS = fDelta / fCMax;
        } else {
            fS = 0;
        }

        fV = fCMax;
    } else {
        fH = 0;
        fS = 0;
        fV = fCMax;
    }

    if (fH < 0) {
        fH = 360 + fH;
    }
}

void HSVtoRGB(float &fR, float &fG, float &fB, float fH, float fS, float fV) {
    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;

    if (0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0;
    } else if (1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0;
    } else if (2 <= fHPrime && fHPrime < 3) {
        fR = 0;
        fG = fC;
        fB = fX;
    } else if (3 <= fHPrime && fHPrime < 4) {
        fR = 0;
        fG = fX;
        fB = fC;
    } else if (4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0;
        fB = fC;
    } else if (5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0;
        fB = fX;
    } else {
        fR = 0;
        fG = 0;
        fB = 0;
    }

    fR += fM;
    fG += fM;
    fB += fM;
}

void brightManager(Image *screen, float bright) {
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        for (int j = 0; j < WINDOW_WIDTH; j++) {
            Pixel img = screen->GetPixel(i, j);
            float h, s, v;
            float r = img.r / 255.0;
            float g = img.g / 255.0;
            float b = img.b / 255.0;
            RGBtoHSV(r, g, b, h, s, v);
            HSVtoRGB(r, g, b, h, s, bright * v);
            Pixel blend = {(uint8_t) (r * 255.0), (uint8_t) (g * 255.0), (uint8_t) (b * 255.0), 255};
            screen->PutPixel(i, j, blend);
        }
    }
}

void boxBlur(Image *screen) {
    for (int i = 1; i < WINDOW_HEIGHT - 1; i++) {
        for (int j = 1; j < WINDOW_WIDTH - 1; j++) {
            Pixel topLeft = screen->GetPixel(i - 1, j + 1);
            Pixel topCenter = screen->GetPixel(i, j + 1);
            Pixel topRight = screen->GetPixel(i + 1, j + 1);
            Pixel midLeft = screen->GetPixel(i - 1, j);
            Pixel currPix = screen->GetPixel(i, j);
            Pixel midRight = screen->GetPixel(i + 1, j);
            Pixel lowLeft = screen->GetPixel(i - 1, j - 1);
            Pixel lowCenter = screen->GetPixel(i, j - 1);
            Pixel lowRight = screen->GetPixel(i + 1, j - 1);
            // Calculate average.
            uint8_t r = (topLeft.r + topCenter.r + topRight.r + midLeft.r + currPix.r + midRight.r + lowLeft.r +
                     lowCenter.r + lowRight.r) / 9 + 3;
            uint8_t g = (topLeft.g + topCenter.g + topRight.g + midLeft.g + currPix.g + midRight.g + lowLeft.g +
                     lowCenter.g + lowRight.g) / 9;
            uint8_t b = (topLeft.b + topCenter.b + topRight.b + midLeft.b + currPix.b + midRight.b + lowLeft.b +
                     lowCenter.b + lowRight.b) / 9;
            uint8_t a = (topLeft.a + topCenter.a + topRight.a + midLeft.a + currPix.a + midRight.a + lowLeft.a +
                     lowCenter.a + lowRight.a) / 9;
            screen->PutPixel(i, j, {r, g, b, a});
        }
    }
}
