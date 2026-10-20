# My3DViewer

Цей проект реалізує 3D-вьювер, який може завантажувати та відображати файли STL.

## Залежності

- GLM, GLFW (встановлюються через vcpkg)
- Glad (завантажується окремо)

## Збірка

cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/шлях/до/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
./build/My3DViewer
