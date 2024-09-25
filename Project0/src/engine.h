#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<sugar_renderer/VAO.h>
#include<sugar_renderer/VBO.h>
#include<sugar_renderer/EBO.h>
#include<sugar_renderer/shaderClass.h>
#include<sugar_renderer/texture.h>
#include<sugar_renderer/renderer.h>
#include<sugar_renderer/gameObject.h>
//#include"camera.h"

#include"logger.h"
#include"shaderConstructor.h"

class Engine
{
public:
	//WINDOW
	GLFWwindow* window;

	//BASIC MESHES
	GLfloat squareVertices[20] =
	{//    COORDINATES       /      UV
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f
	};

	GLuint squareIndices[6] =
	{
		0, 1, 2,
		0, 3, 2
	};

	//FPS COUNTER
	double prevTime = 0.0;
	double crntTime = 0.0;

	double deltaTime;
	double time;

	void Init(Logger& logger, int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* TITLE);
	void TimeTick();
};

#endif