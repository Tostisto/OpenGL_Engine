#pragma once

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include <vector>

#include "ModelLoadType.h"

class ModelLoader
{

private:
	ModelLoadType type;

	std::vector<float> modelVertices;

public:
	ModelLoader(const char* modelPath, ModelLoadType type);

	float* getVertices();
	void processMesh(aiMesh* mesh);
	void processMeshTextures(aiMesh* mesh);
	void processNode(aiNode* node, const aiScene* scene);
	int getVerticesSize();
};