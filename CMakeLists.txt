cmake_minimum_required(VERSION 3.10)

project(My3DViewer)

set(CMAKE_CXX_STANDARD 20)

# Пошук бібліотек
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Додавання виконуваного файлу
add_executable(My3DViewer
    main.cpp
    ViewerWindow.h
    ViewerWindow.cpp
    OpenglRenderSystem.h
    OpenglRenderSystem.cpp
    Vertex.h
    GeometryPrimitives.h
    GeometryPrimitives.cpp
    glad.c
    glad/glad.h
    KHR/khrplatform.h)

# Підключення бібліотек
target_link_libraries(My3DViewer PRIVATE glfw glm::glm)

# Папка проєкту як джерело для пошуку заголовків (glad/glad.h, KHR/khrplatform.h тощо)
target_include_directories(My3DViewer PRIVATE ${CMAKE_SOURCE_DIR})

# GLFW_INCLUDE_NONE не дає GLFW підключати вбудовані функції OpenGL, бо OpenGL завантажує glad
target_compile_definitions(My3DViewer PRIVATE GLFW_INCLUDE_NONE)