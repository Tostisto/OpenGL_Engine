#include "ShaderLoader.h"

ShaderLoader::ShaderLoader(const char* shader_path)
{
	const char* shaderCode = GetShaderCode(shader_path);
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

const char* ShaderLoader::GetShaderCode(const char* shader_path)
{
	FILE* file;
	fopen_s(&file, shader_path, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Failed to open file '%s'\n", shader_path);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* text = (char*)malloc(size + 1);
	fread_s(text, size + 1, size, 1, file);
	fclose(file);

	text[size] = '\0';

	return text;
}
