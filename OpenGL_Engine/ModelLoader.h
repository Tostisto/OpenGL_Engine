#pragma once

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include <vector>

class ModelLoader
{

private:
	std::vector<float> modelVertices;

public:
	ModelLoader(const char* modelPath);

	float* getVertices();
	void processMesh(aiMesh* mesh);
	void processNode(aiNode* node, const aiScene* scene);
	int getVerticesSize();
};