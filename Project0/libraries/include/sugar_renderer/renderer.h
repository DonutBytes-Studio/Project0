#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class Renderer
{
private:
	int transShaderLoc = 0;

public:

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 10.0f);

	void Draw(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size);

	void ClearScreen();
	void ClearScreen(glm::vec4 color);
	void ClearScreen(float r, float g, float b, float a);

};
#endif