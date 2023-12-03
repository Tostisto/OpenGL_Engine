#pragma once

#include "DrawableModel.h"
#include <vector>

#include "FragmentShader.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "VertexShader.h"

//Include GLM  
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

// Transformations
#include "BezierMove.h"
#include "Rotation.h"
#include "Scale.h"
#include "StraightLineMove.h"
#include "TransformCollection.h"
#include "Translation.h"

#include "Window.h"

#include "Camera.h"
#include "CameraControll.h"

#include "ModelLoader.h"

#include "DirectionalLight.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "CubeMap.h"

#include "ModelsManipulation.h"

#include "vector"

class Scene
{
protected:
	CubeMap* cubeMap;

private:
	std::vector<DrawableModel*> drawables;
	std::vector<ShaderProgram*> shaderPrograms;
	std::vector<Light*> lights;

	CameraControll* cameraControll;
	Camera* camera;
	Window* window;

	ModelsManipulation* modelsManipulation;

	void AddCameraControll(CameraControll* cameraControll);

protected:
	void AddDrawable(DrawableModel* drawable);
	void RemoveDrawable(DrawableModel* drawable);

	void AddShaderProgram(ShaderProgram* shaderProgram);
	void RemoveShaderProgram(ShaderProgram* shaderProgram);

	void AddLight(Light* light);
	void RemoveLight(Light* light);

	void AddCubeMap(std::vector<const char*> faces);

	int ModelsCount();

	void AddModelPickers(Model* model, ShaderProgram* shaderProgram);

	virtual void UpdateFrame();

public:
	Scene(Window* window);
	virtual void Create() = 0;

	void Render();
};