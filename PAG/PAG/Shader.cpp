#include "Shader.hpp"

Shader::Shader()
{
	program = glCreateProgram();

	if(!program)
	{
		throw std::runtime_error("Error while creating shader");		
	}
	
	loadShader(GL_VERTEX_SHADER, GL_VERTEX_SHADER_PATH);
	loadShader(GL_FRAGMENT_SHADER, GL_FRAGMENT_SHADER_PATH);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if(!status)
	{		
		std::string errorMessage = "Failed to link shader program";
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			const auto log = static_cast<char*>(malloc(logLen));
			GLsizei written;
			glGetProgramInfoLog(program, logLen, &written, log);
			errorMessage += ". ";
			errorMessage += log;
			free(log);
		}
		throw std::runtime_error(errorMessage);
	}
}


Shader::~Shader()
{
}

void Shader::loadShader(GLint type, std::string fileName)
{
	GLuint shaderObject = glCreateShader(type);

	if (!shaderObject)
	{
		throw std::runtime_error(std::string("Error creating %s.\n", fileName.c_str()));
	}

	std::string shaderCodeString = FileReader::readFile(fileName);

	if (shaderCodeString.empty())
	{
		throw std::runtime_error(std::string("Shader code is empty! Shader name %s\n", fileName.c_str()));
	}

	const char* shaderCode = shaderCodeString.c_str();
	const GLint codeSize = shaderCodeString.size();

	glShaderSource(shaderObject, 1, &shaderCode, &codeSize);
	glCompileShader(shaderObject);

	GLint result;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		std::string errorMessage = std::string("%s compilation failed!\n", fileName.c_str());

		GLint logLen;
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(shaderObject, logLen, &written, log);

			errorMessage += std::string("Shader log: \n");
			errorMessage.append(log);

			free(log);
		}
		throw std::runtime_error(errorMessage);
	}

	glAttachShader(program, shaderObject);
	glDeleteShader(shaderObject);
}

GLuint Shader::getProgram()
{
	return program;
}
