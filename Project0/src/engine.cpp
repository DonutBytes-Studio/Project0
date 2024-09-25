#include"engine.h"

void Engine::Init(Logger& logger, int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* title)
{
	// INIT GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	logger.log(INFO, "GLFW initialized");


	//INIT WINDOW
	Engine::window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);
	if (Engine::window == NULL)
	{
		std::cout << "Failed to create a GLFW window!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(Engine::window);
	logger.log(INFO, "Window initialized");

	//INIT OPENGL
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	logger.log(INFO, "OpenGL initialized");
}

void Engine::TimeTick()
{
	Engine::crntTime = glfwGetTime();
	Engine::deltaTime = crntTime - prevTime;
	Engine::prevTime = Engine::crntTime;
	Engine::time += Engine::deltaTime;
}