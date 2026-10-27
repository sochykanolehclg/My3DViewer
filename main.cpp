#include "ViewerWindow.h"
#include "OpenglRenderSystem.h"
#include "GeometryPrimitives.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cstddef>
#include <vector>

void renderScene(OpenglRenderSystem& rs, const std::vector<Vertex>& data)
{
    rs.renderTriangleSoup(data);
}

void moveCube(OpenglRenderSystem& rs, glm::vec3 offset)
{
    rs.setViewMatrix(glm::translate(rs.getViewMatrix(), offset));
}

int main()
{
    constexpr int width = 640;
    constexpr int height = 480;

    OpenglRenderSystem rs;
    ViewerWindow window("My3DViewer", width, height);

    // Фігури: 1 — куб, 2 — піраміда, 3 — ікосаедр
    const std::vector<std::vector<Vertex>> figures = {
        GeometryPrimitives::createCubeVertices(),
        GeometryPrimitives::createPyramidVertices(),
        GeometryPrimitives::createIcosahedronVertices()
    };
    std::size_t currentFigure = 2;

    // Кути обертання (радіани) і стан перетягування мишею
    float angleX = 0.0f;
    float angleY = 0.0f;
    bool dragging = false;
    double lastX = 0.0;
    double lastY = 0.0;

    auto updateWorld = [&rs, &angleX, &angleY]()
    {
        glm::mat4 world = glm::rotate(glm::mat4(1.0f), angleX, glm::vec3(1.0f, 0.0f, 0.0f))
                        * glm::rotate(glm::mat4(1.0f), angleY, glm::vec3(0.0f, 1.0f, 0.0f));
        rs.setWorldMatrix(world);
    };

    window.setKeyCallback([&](KeyCode key, Action action, Modifier)
    {
        if (action == Action::Release)
            return;

        if (key == KeyCode::UP)
            moveCube(rs, { 0.0f, 0.1f, 0.0f });
        if (key == KeyCode::DOWN)
            moveCube(rs, { 0.0f, -0.1f, 0.0f });
        if (key == KeyCode::LEFT)
            moveCube(rs, { 0.1f, 0.0f, 0.0f });
        if (key == KeyCode::RIGHT)
            moveCube(rs, { -0.1f, 0.0f, 0.0f });

        if (key == KeyCode::Key1)
            currentFigure = 0;
        if (key == KeyCode::Key2)
            currentFigure = 1;
        if (key == KeyCode::Key3)
            currentFigure = 2;

        // R — скинути обертання
        if (key == KeyCode::R)
        {
            angleX = 0.0f;
            angleY = 0.0f;
            updateWorld();
        }
    });

    // Ліва кнопка миші: натиснута — починаємо обертання, відпущена — зупиняємо
    window.setMouseCallback([&](ButtonCode button, Action action, Modifier, double x, double y)
    {
        if (button != ButtonCode::Button_0)
            return;

        dragging = (action == Action::Press);
        lastX = x;
        lastY = y;
    });

    // Рух миші з натиснутою кнопкою повертає фігуру
    window.setCursorPosCallback([&](double x, double y)
    {
        if (!dragging)
            return;

        angleY += static_cast<float>(x - lastX) * 0.01f;
        angleX += static_cast<float>(y - lastY) * 0.01f;
        lastX = x;
        lastY = y;
        updateWorld();
    });

    rs.init();
    rs.setupLight(0, glm::vec3(0, 5, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
    rs.turnLight(0, true);

    glm::vec3 cameraPosition(0.0f, 0.0f, -3.0f);
    glm::vec3 lookAtCenter(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUpVector(0.0f, 1.0f, 0.0f);

    rs.setViewMatrix(glm::lookAt(cameraPosition, lookAtCenter, cameraUpVector));
    rs.setProjectionMatrix(glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.1f, 500.f));
    updateWorld();

    while (!glfwWindowShouldClose(window.getGLFWHandle()))
    {
        rs.setViewport(0, 0, window.getWidth(), window.getHeight());
        rs.clearDisplay(0.5f, 0.5f, 0.5f);
        renderScene(rs, figures[currentFigure]);
        glfwSwapBuffers(window.getGLFWHandle());
        glfwWaitEvents();
    }

    return 0;
}