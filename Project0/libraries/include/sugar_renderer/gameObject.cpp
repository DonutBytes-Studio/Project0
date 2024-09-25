#include"gameObject.h"

GameObject::GameObject(Shader& shader, Renderer& renderer, VAO& vao, GLsizeiptr indicesSize)
{
	GameObject::shader = &shader;
	GameObject::renderer = &renderer;
	GameObject::projection = renderer.projection;
	GameObject::vao = &vao;
	GameObject::indicesSize = indicesSize;
}

void GameObject::Draw()
{
	GameObject::objectMatrix = glm::mat4(1.0f);
	GameObject::transformations = glm::mat4(1.0f);

	GameObject::objectMatrix = glm::translate(GameObject::objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	GameObject::objectMatrix = glm::scale(GameObject::objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	GameObject::transformations = projection * GameObject::objectMatrix;

	(*GameObject::renderer).Draw(*GameObject::shader, GameObject::transformations, (*GameObject::vao), indicesSize);
}

void GameObject::Draw(int numberOfLights, glm::vec4 lightColor[], glm::vec3 lightPos[], int tex0Unit, GLenum baseEnum, Texture base, int normalsUnit, GLenum normalsEnum, Texture normals)
{
	(*GameObject::shader).Activate();

	(*GameObject::shader).setInt("tex0", tex0Unit);
	(*GameObject::shader).setInt("normals", normalsUnit);

	(*GameObject::shader).set3f("crntPos", GameObject::Position.x, GameObject::Position.y, 1.0f);
	(*GameObject::shader).setFloat("ambient", 0.1f);

	for (GLuint i = 0; i < numberOfLights; i++)
	{
		std::string number = std::to_string(i);

		(*GameObject::shader).set3f("pointLights[" + number + "].position", lightPos[i].x, lightPos[i].y, lightPos[i].z);
		(*GameObject::shader).set4f("pointLights[" + number + "].color", lightColor[i].x, lightColor[i].y, lightColor[i].z, lightColor[i].w);
	}

	glActiveTexture(baseEnum);
	base.Bind();
	glActiveTexture(normalsEnum);
	normals.Bind();

	GameObject::objectMatrix = glm::mat4(1.0f);
	GameObject::transformations = glm::mat4(1.0f);

	GameObject::objectMatrix = glm::translate(GameObject::objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	GameObject::objectMatrix = glm::scale(GameObject::objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	GameObject::transformations = projection * GameObject::objectMatrix;

	(*GameObject::renderer).Draw(*GameObject::shader, GameObject::transformations, (*GameObject::vao), indicesSize);
}