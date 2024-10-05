#include"camera.h"

Camera::Camera(float scale)
{
	Renderer::Get().projection = glm::ortho(-scale / 2 * Engine::Get().window_ratio, scale / 2 * Engine::Get().window_ratio, -scale / 2, scale / 2);
	Camera::Scale = scale;
}

void Camera::SetPosition(glm::vec2 pos)
{
	Renderer& renderer = Renderer::Get();

	Camera::Position = pos;

	renderer.view = glm::mat4(1.0f);
	renderer.view = glm::translate(renderer.view, glm::vec3(-Camera::GetPosition(), 0.0f));
}

glm::vec2 Camera::GetPosition()
{
	return Camera::Position;
}


void Camera::SetScale(float scale)
{
	Camera::Scale = scale;
	Renderer::Get().projection = glm::ortho(-scale / 2 * Engine::Get().window_ratio, scale / 2 * Engine::Get().window_ratio, -scale / 2, scale / 2);
}

float Camera::GetScale()
{
	return Camera::Scale;
}