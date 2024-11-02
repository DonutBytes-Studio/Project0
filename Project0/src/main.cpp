#include<chocolate_engine/engine.h>

int main()
{
	//CONSTANTS
	int WINDOW_WIDTH = 720;
	int WINDOW_HEIGHT = 720;
	const float MIN_DISTANCE = 0.05f;

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
	int NB_PARTICLES = 1000;
	std::vector<Particle> particles;
	particles.reserve(NB_PARTICLES);
	Particle* refParticle;

	srand(time(NULL));

	for (unsigned int i = 0; i < NB_PARTICLES; ++i)
	{
		refParticle = nullptr;
		refParticle = new Particle();
		(*refParticle).Scale = glm::vec2(0.02f, 0.02f);
		(*refParticle).Position = glm::vec2(((rand() % 800 + 1) - 400.5f)/100, ((rand() % 800 + 1) - 400.5f)/100);
		//(*refParticle).Position = glm::vec2(0.0f, 0.0f + i/1000.0f);
		particles.push_back(*refParticle);
	}

	glm::vec2 p1, p2, r, a1 = glm::vec2(0.0f, 0.0f);
	float mag_sq, mag, speed = 0.0f;

	Renderer& renderer = Renderer::Get();
	renderer.transformations = glm::mat4(1.0f);

	//MAIN LOOP
	while (!glfwWindowShouldClose(engine.window))
	{
		// START LOOP
		engine.TimeTick();
		Renderer::ClearScreen();

		//FPS
		std::string FPS = std::to_string((1.0 / engine.deltaTime));
		std::string ms = std::to_string(engine.deltaTime * 1000);
		std::string newTitle = "Test - " + FPS + " FPS / " + ms + " ms.";
		glfwSetWindowTitle(engine.window, newTitle.c_str());

		// GAME LOGIC
		circleProgram.Activate();
		vao.Bind();
		for (int i = 0; i < particles.size(); i++)
		{
			refParticle = &particles[i];
			p1 = (*refParticle).Position;
			for (int j = 0; j < particles.size(); j++)
			{
				if (j != i)
				{
					p2 = particles[j].Position;
					if (p1 != p2)
					{
						float m2 = particles[j].Mass;

						r = p2 - p1;
						mag_sq = r.x * r.x + r.y * r.y;
						mag = sqrt(mag_sq);
						a1 = (m2 / (max(mag_sq, MIN_DISTANCE * mag))) * r;

						(*refParticle).Acceleration += a1;
					}
				}
			}

			(*refParticle).Update();

			//RENDER
			speed = glm::length2((*refParticle).Velocity);
			(*refParticle).Color = glm::vec4(speed, speed, (speed/2) + 0.5f, 1.0f);
			(*refParticle).Draw(circleProgram);
		}
		vao.Unbind();

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