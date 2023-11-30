#pragma once

#include "Observer.h"
#include "Camera.h"
#include "Window.h"
#include "ModelsManipulation.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class CameraControll : public Observer
{
private:
	Camera* camera;
	Window* window;
	ModelsManipulation* modelsManipulation;

	float last_x = 0;
	float last_y = 0;

	float current_x = 0;
	float current_y = 0;

	bool lock_camera = false;
	bool left_ctrl_pressed = false;

	void MouseBorderSwitch();

	void GetClickerPixelVariables(GLbyte color[4], GLfloat& depth, GLuint& index);

	glm::vec3 ScreenToWorldCoordinates(int x, int y, GLfloat depth);
	glm::vec3 CalculateWorldPosition(glm::vec3 wincoord);

	glm::vec3 GetMouseClickPosition(GLfloat depth);

public:
	CameraControll(Camera* camera, Window* window, ModelsManipulation* modelsManipulation);

	void MouseMovement(float x_pos, float y_pos);
	void KeyboardMovement();

	void ModelPicker();
	void ModelRemover();

	void Update(Subject* subject, Event type, void* data);
};