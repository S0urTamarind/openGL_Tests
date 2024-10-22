#pragma once
#include "window.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>

class Game
{
public:
    Game();
    void run();

    

private:
    int m_mouseX;
    int m_mouseY;
    int m_type;
    float deltaTime;
    float lastFrame;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::mat4 view;

    Window m_window;
    std::map<std::pair<int, int>, int> m_mapType;

    void sUserInput();
    void mWriteMap();
};