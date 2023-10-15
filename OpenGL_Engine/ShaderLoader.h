#pragma once

#include <fstream>

class ShaderLoader
{
private:
	const char* shaderCode;
	const char* GetShaderCode(const char* shader_path);

public:
	ShaderLoader(const char* shader_path);
	const char* GetShaderCode();
};