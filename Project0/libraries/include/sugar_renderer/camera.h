#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<chocolate_engine/engine.h>
#include<sugar_renderer/renderer.h>


class Camera
{
private:
	glm::vec2 Position = glm::vec2(0.0f, 0.0f);
	float Scale = 0.0f;
public:
	Camera(float scale);

	void SetPosition(glm::vec2 pos);
	glm::vec2 GetPosition();

	void SetScale(float scale);
	float GetScale();
};

#endif