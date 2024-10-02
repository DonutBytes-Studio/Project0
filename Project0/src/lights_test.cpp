/*#include<chocolate_engine/engine.h>

int main()
{
	//CONSTANTS
	int WINDOW_WIDTH = 720;
	int WINDOW_HEIGHT = 720;
	const int LIGHTS_NUMBER = 4;

	// Engine init
	Engine& engine = Engine::Get();
	engine.Init(WINDOW_WIDTH, WINDOW_HEIGHT, "Lights test");

	// VAO
	VAO squareVAO;
	squareVAO.Bind();
	VBO squareVBO(engine.squareVertices, engine.squareVerticesSize);
	EBO squareEBO(engine.squareIndices, engine.squareIndicesSize);
	squareVAO.LinkAttrib(squareVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	squareVAO.LinkAttrib(squareVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

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
	GameObject player(litTextureShaderProgram, squareVAO, engine.squareIndicesSize);

	glm::vec4 lightsColors[LIGHTS_NUMBER] =
	{
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	};

	GameObject lights[LIGHTS_NUMBER]
	{
		{colorShaderProgram, squareVAO, engine.squareIndicesSize},
		{colorShaderProgram, squareVAO, engine.squareIndicesSize},
		{colorShaderProgram, squareVAO, engine.squareIndicesSize},
		{colorShaderProgram, squareVAO, engine.squareIndicesSize}
	};

	//MAIN LOOP
	while (!glfwWindowShouldClose(engine.window))
	{
		// START LOOP
		engine.TimeTick();
		Renderer::ClearScreen();

		// GAME LOGIC

		lights[0].Scale = glm::vec2(0.2f, 0.2f);
		lights[0].Position.x = sin(engine.time) * 3;
		lights[0].Position.y = cos(engine.time) * 3;

		lights[1].Scale = glm::vec2(0.2f, 0.2f);
		lights[1].Position.x = sin(engine.time + 3.14 / 2) * 3;
		lights[1].Position.y = cos(engine.time + 3.14 / 2) * 3;

		lights[2].Scale = glm::vec2(0.2f, 0.2f);
		lights[2].Position.x = sin(engine.time + 3.14) * 3;
		lights[2].Position.y = cos(engine.time + 3.14) * 3;

		lights[3].Scale = glm::vec2(0.2f, 0.2f);
		lights[3].Position.x = sin(engine.time + 3.14 + 3.14 / 2) * 3;
		lights[3].Position.y = cos(engine.time + 3.14 + 3.14 / 2) * 3;

		glm::vec3 lightsPositions[LIGHTS_NUMBER] = {
			glm::vec3(lights[0].Position, 1.0f),
			glm::vec3(lights[1].Position, 1.0f),
			glm::vec3(lights[2].Position, 1.0f),
			glm::vec3(lights[3].Position, 1.0f)
		};

		// RENDER
		colorShaderProgram.Activate();
		for (int i = 0; i < LIGHTS_NUMBER; i++)
		{
			colorShaderProgram.set4f("color", lightsColors[i].r, lightsColors[i].g, lightsColors[i].b, lightsColors[i].a);
			lights[i].Draw();
		}

		player.Draw(LIGHTS_NUMBER, lightsColors, lightsPositions, 0, GL_TEXTURE0, unlitBaseTexture, 1, GL_TEXTURE1, normalsTex);


		// END LOOP
		glfwSwapBuffers(engine.window);
		glfwPollEvents();
	}


	//END
	ObjectsManager::DeleteAllObjects();

	glfwDestroyWindow(engine.window);
	glfwTerminate();
	return 0;
}*/