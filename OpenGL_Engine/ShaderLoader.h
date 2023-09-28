#pragma once

#include <fstream>

class ShaderLoader
{
public:
	ShaderLoader(const char* shader_path);
	const char* GetShaderCode();

private:

	const char* shaderCode;

	const char* GetShaderCode(const char* shader_path);
};