#include "ShaderLoader.h"

ShaderLoader::ShaderLoader(const char* shader_path)
{
	const char* shaderCode = ReadShaderCode(shader_path);
	if (shaderCode == NULL)
	{
		fprintf(stderr, "Failed to load shader code from file '%s'\n", shader_path);
		return;
	}
	else {

		this->shaderCode = shaderCode;
	}
}

const char* ShaderLoader::GetShaderCode()
{
	return this->shaderCode;
}

const char* ShaderLoader::ReadShaderCode(const char* shader_path) {
    std::ifstream file(shader_path);
    if (!file.is_open()) {
        fprintf(stderr, "Failed to open file '%s'\n", shader_path);
        exit(EXIT_FAILURE);
    }

    std::string fileString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    file.close();

    char* text = (char*)malloc(fileString.size() + 1);
    strcpy_s(text, fileString.size() + 1, fileString.c_str());

    return text;
}
