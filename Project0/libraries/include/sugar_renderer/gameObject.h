#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"renderer.h"
#include"texture.h"

class GameObject
{
public:
	glm::vec2 Scale = glm::vec2(1.0f, 1.0f);
	glm::vec2 Position = glm::vec2(0.0f, 0.0f);
	float Rotation = 0.0f;

	glm::mat4 objectMatrix = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	Renderer* renderer;
	VAO* vao;
	Shader* shader;
	GLsizeiptr indicesSize;

	GameObject(Shader& shader, Renderer& renderer, glm::mat4 proj, VAO& vao, GLsizeiptr indicesSize);

	void Draw();
	void Draw(glm::vec4 lightColor[4], glm::vec3 lightPos[4], int tex0Unit, GLenum baseEnum, Texture base, int normalsUnit, GLenum normalsEnum, Texture normals);
};

#endif