#include <glad/glad.h>
#include <string>
#include "FileReader.hpp"
#include "config.hpp"

class Shader
{
private:
	GLuint program;
	void loadShader(GLint type, std::string fileName);
public:
	GLuint getProgram();
	Shader();
	~Shader();
};
