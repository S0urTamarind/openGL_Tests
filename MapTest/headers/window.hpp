#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
    Window(const float windowW, const float windowH);
    Window() = default;

    GLFWwindow *window;

private:
    GLFWwindow *initializeWindow(const float windowW, const float windowH);
};