#include"renderer.h"

void Renderer::Draw(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size)
{
	shader.Activate();

	Renderer::transShaderLoc = glGetUniformLocation(shader.ID, "transformations");
	glUniformMatrix4fv(transShaderLoc, 1, GL_FALSE, glm::value_ptr(transformations));

	vao.Bind();
	glDrawElements(GL_TRIANGLES, size / sizeof(int), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}