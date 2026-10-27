#pragma once

#include "Vertex.h"
#include <cstdint>
#include <vector>

class OpenglRenderSystem
{
public:
	void init(); //must be called after glfw window creation. Set default GL settings

	void clearDisplay(float r, float g, float b);
	void setViewport(double x, double y, double width, double height);
	void renderTriangleSoup(const std::vector<Vertex>& vertices);
	void renderLines(const std::vector<Vertex>& vertices);
	void setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
	void turnLight(uint32_t index, bool enable);

	void setWorldMatrix(const glm::mat4& matrix);
	const glm::mat4& getWorldMatrix() const;

	void setViewMatrix(const glm::mat4& matrix);
	const glm::mat4& getViewMatrix() const;

	void setProjectionMatrix(const glm::mat4& matrix);
	const glm::mat4& getProjMatrix() const;

private:
	enum class eRenderDataType
	{
		Triangles,
		Lines
	};

	void renderData(const std::vector<Vertex>& vertices, eRenderDataType data);

private:
	glm::mat4 worldMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projMatrix = glm::mat4(1.0f);
};