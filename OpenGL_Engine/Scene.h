#pragma once

#include <vector>
#include "Drawable.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"

//Include GLM  
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// Transformations
#include "TransformCollection.h"
#include "Rotation.h"
#include "Translation.h"
#include "Scale.h"

#include "Window.h"

#include "Camera.h"
#include "CameraControll.h"

#include "ModelLoader.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Scene
{
private:
	std::vector<Drawable*> drawables;
	std::vector<ShaderProgram*> shaderPrograms;
	std::vector<Light*> lights;

	CameraControll* cameraControll;

protected:
	void AddCamera(Camera* camera);
	void AddCameraControll(CameraControll* cameraControll);
	void AddWindow(Window* window);

	void AddDrawable(Drawable* drawable);
	void RemoveDrawable(Drawable* drawable);

	void AddShaderProgram(ShaderProgram* shaderProgram);
	void RemoveShaderProgram(ShaderProgram* shaderProgram);

	void AddLight(Light* light);
	void RemoveLight(Light* light);

	virtual void UpdateFrame();

public:
	virtual void Create(Window* window) = 0;

	void Render();
};