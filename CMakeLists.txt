# CMakeList.txt : CMake project for Voxel, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(Voxel)

# Add source to this project's executable.
add_executable (Voxel "src/cpp/Main.cpp" "src/cpp/gui/glad/glad.c" "src/inc/Main.h"  "src/inc/struc/Voxel.h" "src/inc/struc/Chunk.h" "src/cpp/struc/Chunk.cpp" "src/cpp/struc/Voxel.cpp" "src/cpp/struc/World.cpp" "src/inc/struc/World.h" "src/cpp/struc/Coord.cpp" "src/inc/struc/Coord.h" "src/inc/phys/chunkTypes.h" "src/cpp/gui/ChunkRenderer.cpp" "src/inc/gui/ChunkRenderer.h" "src/cpp/gui/shader/Shader.cpp" "src/inc/gui/shader/Shader.h" "src/cpp/gui/window/Window.cpp" "src/inc/gui/window/Window.h" "src/cpp/gui/shader/ShaderProgram.cpp" "src/inc/gui/shader/ShaderProgram.h" "src/cpp/gui/Camera.cpp" "src/inc/gui/Camera.h" "src/cpp/gui/draw/Drawer.cpp" "src/inc/gui/draw/Drawer.h" "src/cpp/gui/draw/VAO.cpp" "src/inc/gui/draw/VAO.h" "src/cpp/gui/draw/VBO.cpp" "src/inc/gui/draw/VBO.h" "src/cpp/gui/draw/Attribute.cpp" "src/inc/gui/draw/Attribute.h" "src/cpp/gui/draw/Drawable.cpp" "src/inc/gui/draw/Drawable.h" "src/cpp/gui/draw/ChunkRenderer.cpp" "src/inc/gui/draw/ChunkRenderer.h")

# TODO: Add tests and install targets if needed.
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/inc)
target_link_libraries(Voxel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib)

