#include"engine.h"

int main()
{
	//CONSTANTS
	int WINDOW_WIDTH = 720;
	int WINDOW_HEIGHT = 720;
	const int LIGHTS_NUMBER = 1;

	// INSTANCES
	Logger logger; // Create logger instance
	Engine engine; // Create engine instance
	engine.Init(logger, WINDOW_WIDTH, WINDOW_HEIGHT, "Project0");
	Renderer renderer;// Create renderer instance

	// VAO
	VAO squareVAO;
	squareVAO.Bind();
	VBO squareVBO(engine.squareVertices, sizeof(engine.squareVertices));
	EBO squareEBO(engine.squareIndices, sizeof(engine.squareIndices));
	squareVAO.LinkAttrib(squareVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	squareVAO.LinkAttrib(squareVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	squareVAO.Unbind();
	squareVBO.Unbind();
	squareEBO.Unbind();

	// SHADERS
	Shader colorShaderProgram("ressources/shaders/default.vert", "ressources/shaders/color.frag");
	Shader litTextureShaderProgram("ressources/shaders/default.vert", litTextureFragmentShader(LIGHTS_NUMBER));
	Shader unlitTextureShaderProgram("ressources/shaders/default.vert", "ressources/shaders/unlitTexture.frag");
	Shader UVShaderProgram("ressources/shaders/default.vert", "ressources/shaders/UV.frag");
	Shader windowCoordShaderProgram("ressources/shaders/default.vert", "ressources/shaders/windowCoord.frag");

	// TEXTURES
	Texture baseTexture("ressources/textures/Donut.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	baseTexture.texUnit(unlitTextureShaderProgram, "tex0", 0);

	Texture unlitBaseTexture("ressources/textures/Donut unshaded.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	unlitBaseTexture.texUnit(litTextureShaderProgram, "tex0", 0);
	Texture normalsTex("ressources/textures/Donut normals.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	normalsTex.texUnit(litTextureShaderProgram, "normals", 1);

	// GAME VARIABLES
	GameObject player(litTextureShaderProgram, renderer, squareVAO, sizeof(engine.squareIndices));
	glm::vec2 velocity(0.0f, 0.0f);
	bool isGrounded = true;

	GameObject light(colorShaderProgram, renderer, squareVAO, sizeof(engine.squareIndices));
	light.Position = glm::vec2(0.0f, 3.0f);
	light.Scale = glm::vec2(0.2f, 0.2f);
	glm::vec4 lightsColors[LIGHTS_NUMBER] =
	{
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	};

	//MAIN LOOP
	while (!glfwWindowShouldClose(engine.window))
	{
		// START LOOP
		engine.TimeTick();
		renderer.ClearScreen();

		// GAME LOGIC
		// Inputs
		if (glfwGetKey(engine.window, GLFW_KEY_SPACE) == GLFW_PRESS && isGrounded)
		{
			velocity.y = 7.0f;
			isGrounded = false;
		}
		else
		{
			velocity.y -= 9.81f * engine.deltaTime;
		}

		velocity.x = 0.0f;
		if (glfwGetKey(engine.window, GLFW_KEY_A) == GLFW_PRESS)
		{
			velocity.x = -3.0f;
		}
		if (glfwGetKey(engine.window, GLFW_KEY_D) == GLFW_PRESS)
		{
			velocity.x = 3.0f;
		}

		player.Position += velocity * (float)engine.deltaTime;

		if (player.Position.y < 0.0f)
		{
			player.Position.y = 0.0f;
			velocity.y = 0.0f;
			isGrounded = true;
		}

		glm::vec3 lightsPositions[LIGHTS_NUMBER] =
		{
			glm::vec3(light.Position, 0.0f)
		};

		// RENDER
		colorShaderProgram.Activate();
		colorShaderProgram.set4f("color", lightsColors[0].r, lightsColors[0].g, lightsColors[0].b, lightsColors[0].a);
		light.Draw();

		player.Draw(LIGHTS_NUMBER, lightsColors, lightsPositions, 0, GL_TEXTURE0, unlitBaseTexture, 1, GL_TEXTURE1, normalsTex);


		// END LOOP
		glfwSwapBuffers(engine.window);
		glfwPollEvents();
	}


	//END
	squareVAO.Delete();
	squareVBO.Delete();
	squareEBO.Delete();
	baseTexture.Delete();
	normalsTex.Delete();
	colorShaderProgram.Delete();
	litTextureShaderProgram.Delete();
	unlitTextureShaderProgram.Delete();
	UVShaderProgram.Delete();
	windowCoordShaderProgram.Delete();

	glfwDestroyWindow(engine.window);
	glfwTerminate();
	return 0;
}