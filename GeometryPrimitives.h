#pragma once

#include "Vertex.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace GeometryPrimitives
{
    std::vector<Vertex> createCubeVertices();
    std::vector<Vertex> createPyramidVertices();
    std::vector<Vertex> createIcosahedronVertices();
}