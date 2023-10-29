#include "ModelLoader.h"

ModelLoader::ModelLoader(const char* modelPath)
{
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes
        | aiProcess_JoinIdenticalVertices
        | aiProcess_CalcTangentSpace;

    const aiScene* scene = importer.ReadFile(modelPath, flags);

    if (!scene || !scene->mRootNode) {

        fprintf(stderr, "ERROR::ASSIMP:: %s\n", importer.GetErrorString());
    
        exit(EXIT_FAILURE);
    }

    processNode(scene->mRootNode, scene);
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void ModelLoader::processMesh(aiMesh* mesh)
{
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        for (unsigned int j = 0; j < 3; j++)
        {
            this->modelVertices.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
            this->modelVertices.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
            this->modelVertices.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);

            this->modelVertices.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
            this->modelVertices.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
            this->modelVertices.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
        }
    }
}

float* ModelLoader::getVertices()
{
    return this->modelVertices.data();
}

int ModelLoader::getVerticesSize()
{
    return this->modelVertices.size();
}