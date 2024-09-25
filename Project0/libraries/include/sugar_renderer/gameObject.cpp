#include"gameObject.h"

GameObject::GameObject(Shader& shader, Renderer& renderer, glm::mat4 proj, VAO& vao, GLsizeiptr indicesSize)
{
	GameObject::shader = &shader;
	GameObject::renderer = &renderer;
	GameObject::projection = proj;
	GameObject::vao = &vao;
	GameObject::indicesSize = indicesSize;
}

void GameObject::Draw()
{
	GameObject::objectMatrix = glm::mat4(1.0f);
	glm::mat4 trans = glm::mat4(1.0f);

	GameObject::objectMatrix = glm::translate(GameObject::objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	GameObject::objectMatrix = glm::scale(GameObject::objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	trans = projection * GameObject::objectMatrix;

	(*GameObject::renderer).Draw(*GameObject::shader, trans, (*GameObject::vao), indicesSize);
}

void GameObject::Draw(glm::vec4 lightColor[4], glm::vec3 lightPos[4], int tex0Unit, GLenum baseEnum, Texture base, int normalsUnit, GLenum normalsEnum, Texture normals)
{
	(*GameObject::shader).Activate();

	(*GameObject::shader).setInt("tex0", tex0Unit);
	(*GameObject::shader).setInt("normals", normalsUnit);

	(*GameObject::shader).set3f("crntPos", GameObject::Position.x, GameObject::Position.y, 1.0f);
	(*GameObject::shader).setFloat("ambient", 0.1f);

	/*for (GLuint i = 0; i < 4; i++)
	{
		std::string number = std::to_string(i);

		(*GameObject::shader).set3f("pointLights[" + number + "].position", lightPos[i].x, lightPos[i].y, lightPos[i].z);
		(*GameObject::shader).set4f("pointLights[" + number + "].color", lightColor[i].x, lightColor[i].y, lightColor[i].z, lightColor[i].w);
	}*/

	(*GameObject::shader).set3f("pointLights[0].position", lightPos[0].x, lightPos[0].y, lightPos[0].z);
	(*GameObject::shader).set4f("pointLights[0].color", lightColor[0].x, lightColor[0].y, lightColor[0].z, lightColor[0].w);

	(*GameObject::shader).set3f("pointLights[1].position", lightPos[1].x, lightPos[1].y, lightPos[1].z);
	(*GameObject::shader).set4f("pointLights[1].color", lightColor[1].x, lightColor[1].y, lightColor[1].z, lightColor[1].w);

	(*GameObject::shader).set3f("pointLights[2].position", lightPos[2].x, lightPos[2].y, lightPos[2].z);
	(*GameObject::shader).set4f("pointLights[2].color", lightColor[2].x, lightColor[2].y, lightColor[2].z, lightColor[2].w);

	(*GameObject::shader).set3f("pointLights[3].position", lightPos[3].x, lightPos[3].y, lightPos[3].z);
	(*GameObject::shader).set4f("pointLights[3].color", lightColor[3].x, lightColor[3].y, lightColor[3].z, lightColor[3].w);

	glActiveTexture(baseEnum);
	base.Bind();
	glActiveTexture(normalsEnum);
	normals.Bind();

	GameObject::objectMatrix = glm::mat4(1.0f);
	glm::mat4 trans = glm::mat4(1.0f);

	GameObject::objectMatrix = glm::translate(GameObject::objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	GameObject::objectMatrix = glm::scale(GameObject::objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	trans = projection * GameObject::objectMatrix;

	(*GameObject::renderer).Draw(*GameObject::shader, trans, (*GameObject::vao), indicesSize);
}