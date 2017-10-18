#include "Shader.hpp"



Shader::Shader()
{
	program = glCreateProgram();

	if(program == 0)
	{
		throw new std::runtime_error("Error while creating shader");		
	}
	
	loadShader(GL_VERTEX_SHADER, "basic.vert", program);
	loadShader(GL_FRAGMENT_SHADER, "basic.frag", program);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if(status == GL_FALSE)
	{
		//throw new std::runtime_error("Failed to link shader program");
		fprintf(stderr, "Failed to link shader program");
		
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);

		if(logLen > 0)
		{
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(program, logLen, &written, log);
			fprintf(stderr, "Program log: \n%s", log);
			free(log);
		}
	}
}


Shader::~Shader()
{
}

std::string Shader::readShader(std::string fileName)
{
	std::string filetext;
	std::string line;
	std::ifstream inFile(fileName);

	if (!inFile)
	{
		fprintf(stderr, "Could not open file %s", fileName.c_str());
		inFile.close();

		return NULL;
	}
	else
	{
		while (inFile.good())
		{
			getline(inFile, line);
			filetext.append(line + "\n");
		}

		inFile.close();

		return filetext;
	}
}

void Shader::loadShader(GLint type, std::string fileName, GLuint & shaderProgram)
{
	GLuint shaderObject = glCreateShader(type);

	if (shaderObject == 0)
	{
		fprintf(stderr, "Error creating %s.\n", fileName.c_str());
		return;
	}

	std::string shaderCodeString = readShader(fileName);

	if (shaderCodeString.empty())
	{
		printf("Shader code is empty! Shader name %s\n", fileName.c_str());
		return;
	}

	const char * shaderCode = shaderCodeString.c_str();
	const GLint codeSize = shaderCodeString.size();

	glShaderSource(shaderObject, 1, &shaderCode, &codeSize);
	glCompileShader(shaderObject);

	GLint result;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		fprintf(stderr, "%s compilation failed!\n", fileName.c_str());

		GLint logLen;
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(shaderObject, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);
			free(log);
		}

		return;
	}

	glAttachShader(shaderProgram, shaderObject);
	glDeleteShader(shaderObject);
}

GLuint Shader::getProgram()
{
	return program;
}
