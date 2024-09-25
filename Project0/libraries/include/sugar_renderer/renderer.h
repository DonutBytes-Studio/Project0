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

	void Draw(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size);

};
#endif