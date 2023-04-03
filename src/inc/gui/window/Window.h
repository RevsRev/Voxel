#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <gui/Camera.h>
#include <io/KeyBoard.h>
#include <io/Mouse.h>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gui/shader/Shader.h"
#include "gui/shader/ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"
#include "struc/Chunk.h"
#include "struc/World.h"
#include <chrono>
#include "gui/Camera.h"

#include "gui/draw/Attribute.h"
#include "gui/draw/VAO.h"
#include "gui/draw/VBO.h"

#include "gui/draw/ChunkRenderer.h"
#include "io/CallBack.h"

#include <phys/GameEngine.h>
#include <phys/Player.h>
#include <gui/WorldUi.h>
#include <util/diagnostic/VoxelDiagnostics.h>

//TODO - Add exceptions when trying to bring up the windows in case of failure

extern void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Window : public HasKeyBoardListener, public HasMouseListener {
private:
	GLFWwindow* window;

	void init(int width, int height);
	void initGlad();
	void processInput(float delTime);

public:
	Window(int width, int height);
	static Window* the();
	static void start();
};