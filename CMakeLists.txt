cmake_minimum_required(VERSION 3.29)
project(NSR)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIR} include)

add_executable(NSR src/main.cpp
        src/ProgramContext.cpp
        include/ProgramContext.h
        include/UserInterface.h
        src/UI/UserInterface.cpp
        include/Simulation/Scene.h
        include/Viewport.h
        src/UI/Widget/3D/Viewport.cpp
        include/Render/SoftwareRenderer.h
        include/Simulation/Scene.h
        src/Simulation/Scene.cpp
        src/Render/SoftwareRenderer.cpp
        src/util/Mathematics/Vector/Vec3.cpp
        include/Mathematics.h
        src/util/Mathematics/Tri.cpp
        src/util/Mathematics/Quaternion.cpp
        include/Mathematics/Matrix4f.h
        src/util/Mathematics/Matrix4f.cpp
        src/Render/Camera.cpp
        src/util/Mathematics/Transformation.cpp
        src/util/Mathematics/Axes.cpp
        include/Interface/Commands.h
        src/Commands.cpp
        include/Render/PolygonMesh.h
        src/Render/PolygonMesh.cpp
        include/Render/Primitives.h
        src/Render/Primitives.cpp
        include/Storage/WavefrontObject.h
        src/util/Storage/WavefrontObject.cpp
        include/Render/PointMesh.h
        src/Render/PointMesh.cpp
        src/util/Mathematics/Vector/Vec2.cpp)
target_link_libraries(NSR SDL2::SDL2 SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static)
