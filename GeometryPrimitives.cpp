#include "GeometryPrimitives.h"

std::vector<Vertex> GeometryPrimitives::createCubeVertices()
{
    std::vector<Vertex> cubeVertices;

    // Define the 8 unique vertices of the cube
    glm::vec3 positions[] = {
        {-0.5f, -0.5f, -0.5f}, // 0
        { 0.5f, -0.5f, -0.5f}, // 1
        { 0.5f,  0.5f, -0.5f}, // 2
        {-0.5f,  0.5f, -0.5f}, // 3
        {-0.5f, -0.5f,  0.5f}, // 4
        { 0.5f, -0.5f,  0.5f}, // 5
        { 0.5f,  0.5f,  0.5f}, // 6
        {-0.5f,  0.5f,  0.5f}  // 7
    };

    // Define the normals for each face of the cube
    glm::vec3 normals[] = {
        { 0.0f,  0.0f, -1.0f}, // Front face
        { 0.0f,  0.0f,  1.0f}, // Back face
        {-1.0f,  0.0f,  0.0f}, // Left face
        { 1.0f,  0.0f,  0.0f}, // Right face
        { 0.0f, -1.0f,  0.0f}, // Bottom face
        { 0.0f,  1.0f,  0.0f}  // Top face
    };

    // Define a color for each face
    glm::vec3 colors[] = {
        {1.0f, 0.0f, 0.0f}, // Red
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {1.0f, 1.0f, 0.0f}, // Yellow
        {1.0f, 0.0f, 1.0f}, // Magenta
        {0.0f, 1.0f, 1.0f}  // Cyan
    };

    // Define the indices for the 12 triangles of the cube
    unsigned int indices[] = {
        0, 1, 2,  2, 3, 0,  // Front face
        4, 5, 6,  6, 7, 4,  // Back face
        0, 3, 7,  7, 4, 0,  // Left face
        1, 5, 6,  6, 2, 1,  // Right face
        0, 1, 5,  5, 4, 0,  // Bottom face
        3, 2, 6,  6, 7, 3   // Top face
    };

    // Construct the vertex data for each triangle
    for (int i = 0; i < 36; i++)
    {
        unsigned int index = indices[i];
        int face = i / 6; // Determine the face based on the triangle index

        Vertex vertex;
        vertex.position = positions[index];
        vertex.normal = normals[face];
        vertex.color = colors[face];

        cubeVertices.push_back(vertex);
    }

    return cubeVertices;
}



namespace
{
    // Додає трикутник. Нормаль береться з порядку вершин і, якщо дивиться всередину,
    // перевертається, щоб вказувати назовні від центру фігури (0, 0, 0).
    void addTriangle(std::vector<Vertex>& out, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color)
    {
        glm::vec3 n = glm::normalize(glm::cross(b - a, c - a));
        glm::vec3 centroid = (a + b + c) / 3.0f;
        if (glm::dot(n, centroid) < 0.0f)
            n = -n;

        out.push_back({ a, n, color });
        out.push_back({ b, n, color });
        out.push_back({ c, n, color });
    }
}

std::vector<Vertex> GeometryPrimitives::createPyramidVertices()
{
    std::vector<Vertex> pyramid;

    // Вершини основи (квадрат) і верхівка
    const glm::vec3 p0{ -0.5f, -0.5f, -0.5f };
    const glm::vec3 p1{  0.5f, -0.5f, -0.5f };
    const glm::vec3 p2{  0.5f, -0.5f,  0.5f };
    const glm::vec3 p3{ -0.5f, -0.5f,  0.5f };
    const glm::vec3 top{ 0.0f,  0.5f,  0.0f };

    const glm::vec3 baseColor{ 0.8f, 0.8f, 0.8f };

    // Основа: два трикутники
    addTriangle(pyramid, p0, p1, p2, baseColor);
    addTriangle(pyramid, p0, p2, p3, baseColor);

    // Чотири бічні грані
    addTriangle(pyramid, p0, p1, top, { 1.0f, 0.0f, 0.0f });
    addTriangle(pyramid, p1, p2, top, { 0.0f, 1.0f, 0.0f });
    addTriangle(pyramid, p2, p3, top, { 0.0f, 0.0f, 1.0f });
    addTriangle(pyramid, p3, p0, top, { 1.0f, 1.0f, 0.0f });

    return pyramid;
}

std::vector<Vertex> GeometryPrimitives::createIcosahedronVertices()
{
    // Вершини ікосаедра через золотий перетин, потім нормалізуємо до радіуса 0.5
    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;
    std::vector<glm::vec3> p = {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };
    for (glm::vec3& v : p)
        v = glm::normalize(v) * 0.5f;

    // Усі ребра ікосаедра мають однакову довжину (мінімальну відстань між вершинами)
    float edge = std::numeric_limits<float>::max();
    for (size_t i = 0; i < p.size(); ++i)
        for (size_t j = i + 1; j < p.size(); ++j)
            edge = std::min(edge, glm::distance(p[i], p[j]));

    auto isEdge = [&](size_t i, size_t j)
    {
        return std::fabs(glm::distance(p[i], p[j]) - edge) < 1e-4f;
    };

    // Грань — це три вершини, попарно з'єднані ребрами
    std::vector<Vertex> icosahedron;
    int faceIndex = 0;
    for (size_t i = 0; i < p.size(); ++i)
        for (size_t j = i + 1; j < p.size(); ++j)
            for (size_t k = j + 1; k < p.size(); ++k)
            {
                if (!isEdge(i, j) || !isEdge(j, k) || !isEdge(k, i))
                    continue;

                // Кожна грань має свій колір
                float n = static_cast<float>(faceIndex++);
                glm::vec3 color{
                    0.5f + 0.5f * std::sin(n * 1.3f),
                    0.5f + 0.5f * std::sin(n * 0.7f + 2.0f),
                    0.5f + 0.5f * std::sin(n * 2.1f + 4.0f)
                };
                addTriangle(icosahedron, p[i], p[j], p[k], color);
            }

    return icosahedron;
}