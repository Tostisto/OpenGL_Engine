#pragma once

#include <fstream>

#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

class ShaderLoader
{
private:
	const char* shaderCode;
	const char* ReadShaderCode(const char* shader_path);

public:
	ShaderLoader(const char* shader_path);
	const char* GetShaderCode();
};