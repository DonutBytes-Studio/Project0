#include"shaderConstructor.h"

std::string litTextureFragmentShader(int numberOfLights)
{
	std::string number = std::to_string(numberOfLights);

	return get_file_contents("ressources/shaders/parts/litTextureShader1.txt") + number + get_file_contents("ressources/shaders/parts/litTextureShader2.txt");
}