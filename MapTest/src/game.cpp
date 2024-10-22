#include "game.hpp"

Game::Game() : m_mouseX{-1}, m_mouseY{-1}, m_type{0}, cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)}, cameraFront{glm::vec3(0.0f, 0.0f, 1.0f)},
               cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)}, cameraRight{glm::vec3(1.0f, 0.0f, 0.0f)}, deltaTime{0.0f}, lastFrame{0.0f}
{
    m_window = Window(2560, 1440);
}

void Game::run()
{
    while (!glfwWindowShouldClose(m_window.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        sUserInput();

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window.window);
        glfwPollEvents();
    }
    glfwTerminate();
    mWriteMap();
}

void Game::mWriteMap()
{
    std::ofstream outFile("./../../MapTest/resources/map.txt");
    if (outFile.is_open())
    {
        for (const auto &entry : m_mapType)
        {
            outFile << entry.first.first << " " << entry.first.second << " " << entry.second << "\n";
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing\n";
    }
}

void Game::sUserInput()
{
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(m_window.window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (glfwGetKey(m_window.window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraUp;
    }
    if (glfwGetKey(m_window.window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraRight;
    }
    if (glfwGetKey(m_window.window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraRight;
    }

    for (int i = 0; i <= 9; ++i)
    {
        if (glfwGetKey(m_window.window, GLFW_KEY_0 + i) == GLFW_PRESS)
        {
            m_mouseX = -1;
            m_mouseY = -1;
            m_type = i;
        }
    }

    if (glfwGetMouseButton(m_window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_type != 0)
    {
        double x, y;
        glfwGetCursorPos(m_window.window, &x, &y);
        int mouseX = static_cast<int>(x) / 80;
        int mouseY = static_cast<int>(y) / 80;
        if (!(m_mouseX == mouseX && m_mouseY == mouseY))
        {
            m_mouseX = mouseX;
            m_mouseY = mouseY;
            if (m_type == 9)
            {
                m_mapType.erase(std::make_pair(m_mouseX, m_mouseY));
            }
            else
            {
                m_mapType[std::make_pair(m_mouseX, m_mouseY)] = m_type;
            }
        }
    }

    if (glfwGetKey(m_window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window.window, true);
    }
}
