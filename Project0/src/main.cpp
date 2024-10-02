#include<chocolate_engine/engine.h>

int main()
{
	struct Body
	{
		GameObject* gameObject;

		Body(GameObject* g)
		{
			gameObject = g;
		}


		glm::vec2 Velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 Acceleration = glm::vec2(0.0f, 0.0f);
		float Mass = 0.001f;

		void Update(float deltaTime)
		{
			(*gameObject).Position += Velocity * deltaTime;
			Velocity += Acceleration * deltaTime;
			Acceleration = glm::vec2(0.0f, 0.0f);
		}
	};

	//CONSTANTS
	int WINDOW_WIDTH = 720;
	int WINDOW_HEIGHT = 720;
	const int LIGHTS_NUMBER = 1;
	const float MIN_DISTANCE = 0.01f;

	// Engine init
	Engine& engine = Engine::Get();
	engine.Init(WINDOW_WIDTH, WINDOW_HEIGHT, "Project0");

	// VAO
	VAO vao;
	vao.Bind();
	VBO vbo(engine.triangleVertices, engine.triangleVerticesSize);
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	// SHADERS
	Shader circleProgram("ressources/shaders/default.vert", "ressources/shaders/circle.frag");

	// TEXTURES

	// GAME VARIABLES
	int NB_PARTICLES = 800;
	std::vector<Body> bodies;
	bodies.reserve(NB_PARTICLES);
	Body* refBody;

	srand(time(NULL));

	for (unsigned int i = 0; i < NB_PARTICLES; ++i)
	{
		refBody = nullptr;
		refBody = new Body(new GameObject(circleProgram, vao, engine.triangleVerticesSize));
		(*refBody).gameObject->Scale = glm::vec2(0.02f, 0.02f);
		(*refBody).gameObject->Position = glm::vec2(((rand() % 800 + 1) - 400.5f)/100, ((rand() % 800 + 1) - 400.5f)/100);
		bodies.push_back(*refBody);
	}

	glm::vec2 p1, p2, r, a1 = glm::vec2(0.0f, 0.0f);
	float mag_sq, mag = 0.0f;

	//MAIN LOOP
	while (!glfwWindowShouldClose(engine.window))
	{
		// START LOOP
		engine.TimeTick();
		Renderer::ClearScreen();

		// GAME LOGIC

		for (int i = 0; i < bodies.size(); i++)
		{
			p1 = bodies[i].gameObject->Position;
			for (int j = 0; j < bodies.size(); j++)
			{
				if (j != i)
				{
					p2 = bodies[j].gameObject->Position;
					float m2 = bodies[j].Mass;

					r = p2 - p1;
					mag_sq = r.x * r.x + r.y * r.y;
					mag = sqrt(mag_sq);
					a1 = (m2 / (max(mag_sq, MIN_DISTANCE) * mag)) * r;

					bodies[i].Acceleration += a1;
				}
			}
		}

		// RENDER
		circleProgram.Activate();

		for (int i = 0; i < bodies.size(); i++)
		{
			bodies[i].Update(engine.deltaTime);
			circleProgram.set4f("color", (bodies[i].Velocity.x + 0.5f), (bodies[i].Velocity.y + 0.5f), 0.0f, 1.0f);
			bodies[i].gameObject->DrawArray(0, 3);
		}

		// END LOOP
		glfwSwapBuffers(engine.window);
		glfwPollEvents();
	}


	//END
	ObjectsManager::DeleteAllObjects();

	glfwDestroyWindow(engine.window);
	glfwTerminate();
	return 0;
}