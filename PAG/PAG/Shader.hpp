#include <glad/glad.h>
#include <string>
#include "FileReader.hpp"

class Shader
{
private:
	GLuint program;
	void loadShader(GLint type, std::string fileName, GLuint& shaderProgram);
public:
	GLuint getProgram();
	Shader();
	~Shader();
};
