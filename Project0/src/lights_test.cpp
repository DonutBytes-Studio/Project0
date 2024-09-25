/*#include <iostream>
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

int main()
{
	//CONSTANTS
	int WINDOW_WIDTH = 720;
	int WINDOW_HEIGHT = 720;

	//VERTICES & INDICES

	GLfloat squareVertices[] =
	{//    COORDINATES       /      UV
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f
	};

	GLuint squareIndices[] =
	{
		0, 1, 2,
		0, 3, 2
	};

	// INIT GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	//INIT WINDOW
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//INIT OPENGL
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//VAO
	VAO squareVAO;

	squareVAO.Bind();

	VBO squareVBO(squareVertices, sizeof(squareVertices));
	EBO squareEBO(squareIndices, sizeof(squareIndices));

	squareVAO.LinkAttrib(squareVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	squareVAO.LinkAttrib(squareVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	squareVAO.Unbind();
	squareVBO.Unbind();
	squareEBO.Unbind();


	//SHADERS
	Shader colorShaderProgram("ressources/shaders/default.vert", "ressources/shaders/color.frag");
	Shader textureShaderProgram("ressources/shaders/default.vert", "ressources/shaders/texture.frag");
	Shader UVShaderProgram("ressources/shaders/default.vert", "ressources/shaders/UV.frag");
	Shader windowCoordShaderProgram("ressources/shaders/default.vert", "ressources/shaders/windowCoord.frag");

	//RENDER
	Renderer renderer;

	//TEXTURE
	Texture whiteTexture("ressources/textures/Donut unshaded.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteTexture.texUnit(textureShaderProgram, "tex0", 0);

	Texture normalsTex("ressources/textures/Donut normals.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	normalsTex.texUnit(textureShaderProgram, "normals", 1);

	//FPS COUNTER
	double prevTime = 0.0;
	double crntTime = 0.0;

	double deltaTime;
	unsigned int counter = 0;

	//ANIMATION
	double timer = 0.0;
	unsigned int frame = 0;

	//glfwSwapInterval(1); // Turn Vsync on
	glEnable(GL_DEPTH_TEST);

	//VECTORIAL MATRICES & STUFF

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 trans = glm::mat4(1.0f);

	int transLoc = 0;

	projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 10.0f);

	//################################################## GAME VARIABLES

	GameObject player(textureShaderProgram, renderer, projection, squareVAO, sizeof(squareIndices));

	glm::vec4 lightColors[4] =
	{
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	};

	GameObject light1(colorShaderProgram, renderer, projection, squareVAO, sizeof(squareIndices));
	GameObject light2(colorShaderProgram, renderer, projection, squareVAO, sizeof(squareIndices));
	GameObject light3(colorShaderProgram, renderer, projection, squareVAO, sizeof(squareIndices));
	GameObject light4(colorShaderProgram, renderer, projection, squareVAO, sizeof(squareIndices));

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//################################################# TIME MANAGER
		crntTime = glfwGetTime();
		deltaTime = crntTime - prevTime;

		std::string FPS = std::to_string((1.0 / deltaTime));
		std::string ms = std::to_string(deltaTime * 1000);
		std::string newTitle = "Test - " + FPS + " FPS / " + ms + " ms.";
		glfwSetWindowTitle(window, newTitle.c_str());

		prevTime = crntTime;

		timer += deltaTime;
		//################################################## INPUTS

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player.Position += glm::vec2(0.0f, 0.5f) * (float)deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player.Position += glm::vec2(-0.5f, 0.0f) * (float)deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player.Position += glm::vec2(0.0f, -0.5f) * (float)deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player.Position += glm::vec2(0.5f, 0.0f) * (float)deltaTime;
		}

		light1.Scale = glm::vec2(0.2f, 0.2f);
		light1.Position.x = sin(timer) * 3;
		light1.Position.y = cos(timer) * 3;

		light2.Scale = glm::vec2(0.2f, 0.2f);
		light2.Position.x = sin(timer + 3.14 / 2) * 3;
		light2.Position.y = cos(timer + 3.14 / 2) * 3;

		light3.Scale = glm::vec2(0.2f, 0.2f);
		light3.Position.x = sin(timer + 3.14) * 3;
		light3.Position.y = cos(timer + 3.14) * 3;

		light4.Scale = glm::vec2(0.2f, 0.2f);
		light4.Position.x = sin(timer + 3.14 + 3.14 / 2) * 3;
		light4.Position.y = cos(timer + 3.14 + 3.14 / 2) * 3;

		glm::vec3 lightPositions[4] = {
			glm::vec3(light1.Position, 1.0f),
			glm::vec3(light2.Position, 1.0f),
			glm::vec3(light3.Position, 1.0f),
			glm::vec3(light4.Position, 1.0f)
		};

		//################################################## RENDER

		glClearColor(0.11f, 0.09f, 0.12f, 1.0f);					 // Specify the background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			 // Clean the back buffer and assign the new color to it

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		//##########################################

		colorShaderProgram.Activate();

		colorShaderProgram.set4f("color", lightColors[0].x, lightColors[0].y, lightColors[0].z, lightColors[0].w);
		light1.Draw();

		colorShaderProgram.set4f("color", lightColors[1].x, lightColors[1].y, lightColors[1].z, lightColors[1].w);
		light2.Draw();

		colorShaderProgram.set4f("color", lightColors[2].x, lightColors[2].y, lightColors[2].z, lightColors[2].w);
		light3.Draw();

		colorShaderProgram.set4f("color", lightColors[3].x, lightColors[3].y, lightColors[3].z, lightColors[3].w);
		light4.Draw();

		player.Draw(lightColors, lightPositions, 0, GL_TEXTURE0, whiteTexture, 1, GL_TEXTURE1, normalsTex);

		//##################################################
		glfwSwapBuffers(window);									 // Swap the back buffer with the front buffer
		glfwPollEvents();										     // Take care of all GLFW events
		//##################################################
	}

	//END
	squareVAO.Delete();
	squareVBO.Delete();
	squareEBO.Delete();
	whiteTexture.Delete();
	normalsTex.Delete();
	colorShaderProgram.Delete();
	textureShaderProgram.Delete();
	UVShaderProgram.Delete();
	windowCoordShaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}*/