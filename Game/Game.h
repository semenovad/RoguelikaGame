#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#define GLFW_DLL

#include <GLFW/glfw3.h>
#include "GameLevel.h"
#include "structure.h"

struct InputState {
    bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
    GLfloat lastX = 400, lastY = 300; //исходное положение мыши
    bool firstMouse = true;
    bool captureMouse = true;  // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;
};

class Game {
public:
    int width;
    int height;
    Image *screen;

    bool end;
    bool lose;
    gameState state;
    InputState inputState;

    std::vector<GameLevel> Levels;
    unsigned int Level;

    void Init();

    double time;
    void Draw(float dt);
    void ProcessInput(double dt);
    void Render(float dt);

    Game(unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT);
    ~Game();
};

#endif //MAIN_GAME_H
