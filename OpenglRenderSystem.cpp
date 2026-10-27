#include "OpenglRenderSystem.h"

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

namespace
{
    GLenum GetLight(uint32_t index)
    {
        switch (index)
        {
        case 0: return GL_LIGHT0;
        case 1: return GL_LIGHT1;
        case 2: return GL_LIGHT2;
        case 3: return GL_LIGHT3;
        case 4: return GL_LIGHT4;
        case 5: return GL_LIGHT5;
        case 6: return GL_LIGHT6;
        case 7: return GL_LIGHT7;
        }
        return GL_LIGHT0;
    }
}

void OpenglRenderSystem::init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LEQUAL);
}

void OpenglRenderSystem::clearDisplay(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRenderSystem::setViewport(double x, double y, double width, double height)
{
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(width), static_cast<GLint>(height));
}

void OpenglRenderSystem::renderTriangleSoup(const std::vector<Vertex>& vertices)
{
    renderData(vertices, eRenderDataType::Triangles);
}

void OpenglRenderSystem::renderLines(const std::vector<Vertex>& vertices)
{
    renderData(vertices, eRenderDataType::Lines);
}

void OpenglRenderSystem::setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is)
{
    GLenum glLight = GetLight(index);

    glLightfv(glLight, GL_AMBIENT, glm::value_ptr(glm::vec4(Ia, 1.0f)));
    glLightfv(glLight, GL_DIFFUSE, glm::value_ptr(glm::vec4(Id, 1.0f)));
    glLightfv(glLight, GL_SPECULAR, glm::value_ptr(glm::vec4(Is, 1.0f)));

    glLightfv(glLight, GL_POSITION, glm::value_ptr(glm::vec4(position, 1.0f)));

    if (!glIsEnabled(GL_LIGHTING))
        glEnable(GL_LIGHTING);
}

void OpenglRenderSystem::turnLight(uint32_t index, bool enable)
{
    GLenum glLight = GetLight(index);

    if (enable)
        glEnable(glLight);
    else
        glDisable(glLight);
}

void OpenglRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
    worldMatrix = matrix;
}

const glm::mat4& OpenglRenderSystem::getWorldMatrix() const
{
    return worldMatrix;
}

void OpenglRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
    viewMatrix = matrix;
}

const glm::mat4& OpenglRenderSystem::getViewMatrix() const
{
    return viewMatrix;
}

void OpenglRenderSystem::setProjectionMatrix(const glm::mat4& matrix)
{
    projMatrix = matrix;
}

const glm::mat4& OpenglRenderSystem::getProjMatrix() const
{
    return projMatrix;
}

void OpenglRenderSystem::renderData(const std::vector<Vertex>& vertices, eRenderDataType data)
{
    glm::mat4 modelView = viewMatrix * worldMatrix;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(modelView));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projMatrix));

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    if (!glIsEnabled(GL_COLOR_MATERIAL))
        glEnable(GL_COLOR_MATERIAL);

    if (data == eRenderDataType::Triangles)
    {
        glDepthRange(0.01, 1.0);
        glBegin(GL_TRIANGLES);
    }
    else if (data == eRenderDataType::Lines)
    {
        glLineWidth(1.0f);
        glBegin(GL_LINES);
    }

    for (const Vertex& curVert : vertices)
    {
        glNormal3f(curVert.normal.x, curVert.normal.y, curVert.normal.z);
        glColor3f(curVert.color.r, curVert.color.g, curVert.color.b);
        glVertex3f(curVert.position.x, curVert.position.y, curVert.position.z);
    }
    glEnd();
}