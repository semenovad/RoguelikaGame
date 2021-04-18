#include "Game.h"
#include "GameLevel.h"
#include "usefulFunc.h"

GameObject *player;
std::vector<std::vector<GameObject*>> evils(2);
std::vector<std::vector<GameObject*>> details(2);
std::vector<std::vector<GameObject*>> emptys(2);
GameObject *openDoor, *closeDoor;

void Game::Init() {
    time = 0.075;
    lose = false;
    end = false;
    screen = new Image(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    openDoor = new GameObject({0, 0});
    openDoor->setImage("../resources/openDoor.png");
    closeDoor = new GameObject({0, 0});
    closeDoor->setImage("../resources/closeDoor.png");

    GameLevel one;
    one.Load("../resources/level1", {40, 40}, 0);
    GameLevel two;
    two.Load("../resources/level2", {40, 40}, 1);

    player = new GameObject(one.playerStartPos);
    player->isPlayer = true;
    player->setImage("../resources/walk/down.png");
    player->setImage("../resources/walk/left.png");
    player->setImage("../resources/walk/right.png");
    player->setImage("../resources/walk/up.png");

    for (auto item : one.evilStartPos) {
        GameObject *evil;
        evil = new GameObject(item);
        evil->setImage("../resources/evil/right.png");
        evil->setImage("../resources/evil/up.png");
        evil->setImage("../resources/evil/left.png");
        evil->setImage("../resources/evil/down.png");
        evils[0].push_back(evil);
    }

    for (auto item : one.torchPos) {
        GameObject *torch;
        torch = new GameObject(item);
        torch->setImage("../resources/details/torch1.png");
        torch->setImage("../resources/details/torch2.png");
        torch->setImage("../resources/details/torch3.png");
        torch->setImage("../resources/details/torch4.png");
        torch->time = time;
        time += 0.075;
        details[0].push_back(torch);
    }

    for (auto item : one.emptyPos) {
        GameObject *empty;
        empty = new GameObject(item);
        empty->setImage("../resources/water/water1.png");
        empty->setImage("../resources/water/water2.png");
        empty->setImage("../resources/water/water3.png");
        empty->setImage("../resources/water/water4.png");
        empty->time = 0;
        emptys[0].push_back(empty);
    }

    for (auto item : two.evilStartPos) {
        GameObject *evil;
        evil = new GameObject(item);
        evil->setImage("../resources/evil/right.png");
        evil->setImage("../resources/evil/up.png");
        evil->setImage("../resources/evil/left.png");
        evil->setImage("../resources/evil/down.png");
        evils[1].push_back(evil);
    }

    time = 0;
    for (auto item : two.emptyPos) {
        GameObject *empty;
        empty = new GameObject(item);
        empty->setImage("../resources/lava/lava1.png");
        empty->setImage("../resources/lava/lava2.png");
        empty->time = 0;
        emptys[1].push_back(empty);
    }

    time = 0.075;
    for (auto item : two.torchPos) {
        GameObject *torch;
        torch = new GameObject(item);
        torch->setImage("../resources/details/torch1.png");
        torch->setImage("../resources/details/torch2.png");
        torch->setImage("../resources/details/torch3.png");
        torch->setImage("../resources/details/torch4.png");
        torch->time = time;
        time += 0.075;
        details[1].push_back(torch);
    }

    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Level = 0;
}
void Game::ProcessInput(double dt) {
    player->time += dt;

    evils[Level][0]->time += dt;
    if (evils[Level][0]->time >= 0.2) {
        for (auto item : evils[Level]) {
            item->staticMove(dt, Levels[Level].tileData, &state);
        }
        evils[Level][0]->time = 0;
    }

    if (player->time >= 0.2) {
        if (inputState.keys[GLFW_KEY_W] && player->pos.y <= 39 && player->pos.y > 0) {
            player->move(MovementDir::DOWN, dt, Levels[Level].tileData, &state);
            player->time = 0;
        }
        else if (inputState.keys[GLFW_KEY_S] && player->pos.y < 39 && player->pos.y >= 0) {
            player->move(MovementDir::UP, dt, Levels[Level].tileData, &state);
            player->time = 0;
        }
        else if (inputState.keys[GLFW_KEY_A] && player->pos.x > 0 && player->pos.x <= 39) {
            player->move(MovementDir::LEFT, dt, Levels[Level].tileData, &state);
            player->time = 0;
        }
        else if (inputState.keys[GLFW_KEY_D] && player->pos.x >= 0 && player->pos.x < 39) {
            player->move(MovementDir::RIGHT, dt, Levels[Level].tileData, &state);
            player->time = 0;
        }
        else if (inputState.keys[GLFW_KEY_E]) {
            Point tmp = isDoor(Levels[Level].tileData, player->pos.x, player->pos.y, player->lastMove);
            if (tmp.x != -1) {
                doorsChanges(Levels[Level].tileData, tmp);
            }
            player->time = 0;
        };
    }
}

void Game::Draw(float dt) {
    double maxTime;
    if (Level == 0) maxTime = 0.1;
    else maxTime = 0.5;
    drawIntoScreen(screen, Levels[Level].levelMap, 0, 0);
    for (auto item : emptys[Level]) {
        item->time += dt;
        drawIntoScreen(screen, item->image[item->dir], item->pos.x, item->pos.y);
        if (item->time >= maxTime) {
            item->dir = (item->dir + 1) % (item->image.size());
            item->time = 0;
        }
    }
    drawIntoScreen(screen, player->image[player->dir], player->pos.x, player->pos.y);
    for (auto item : evils[Level]) {
        drawIntoScreen(screen, item->image[item->dir], item->pos.x, item->pos.y);
    }
    for (auto item : details[Level]) {
        item->time += dt;
        drawIntoScreen(screen, item->image[item->dir], item->pos.x, item->pos.y);
        if (item->time >= 0.4) {
            item->dir = (item->dir + 1) % (item->image.size());
            item->time = 0;
        }
    }
    drawDoors(screen, openDoor->image[openDoor->dir], closeDoor->image[closeDoor->dir], Levels[Level].doorPos,
              Levels[Level].tileData);
}
void Game::Render(float dt) {
    double loadSpeed = 0.8;
    if (!end) {
        if (this->state == ACTIVE) {
            Draw(dt);
        }
        else if (this->state == WIN_LEVEL) {
            Image *levelUp;
            if (Level == 1) {
                levelUp = new Image("../resources/youWin.png");
            } else levelUp = new Image("../resources/levelUp.png");

            drawIntoScreen(screen, levelUp, 0, 0);

            time = 0;
            this->state = BRIGHT_OFF;
        }
        else if (this->state == LOSE) {
            lose = true;

            Image *gameOver;
            gameOver = new Image("../resources/gameOver3.png");
            Draw(dt);
            drawIntoScreen(screen, gameOver, 0, 0);

            time = 0;
            this->state = BLUR;
        }
        else if (this->state == BLUR){
            if (lose && time <= 1) {
                boxBlur(screen);
                time += dt;
            }
            else {
                time = 0;
                this->state = BRIGHT_OFF;
            }
        }
        else if (this->state == BRIGHT_OFF) {
            if (time <= loadSpeed) {
                brightManager(screen, 1 - time / loadSpeed);
                time += dt;
            } else {
                time = 0;
                if (lose) end = true;
                else {
                    if (Level == Levels.size() - 1) end = true;
                    int level = this->Level;
                    this->Level = level + 1;
                    player->pos = Levels[Level].playerStartPos;
                    player->dir = 0;

                    this->state = BRIGHT_ON;
                }
            }
        } else if (this->state == BRIGHT_ON) {
            if (time <= loadSpeed) {
                Draw(dt);
                brightManager(screen, time / loadSpeed);
                time += dt;
            } else {
                time = 0;
                this->state = ACTIVE;
            }
        }
        glRasterPos2f(-1, 1);
        glPixelZoom(1, -1);
        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screen->Data());
    }

}

Game::Game(unsigned int width, unsigned int height) : state(ACTIVE), width(width), height(height) {

}

Game::~Game() {

}