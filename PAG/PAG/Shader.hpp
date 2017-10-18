#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>

class Shader
{
private:
	GLuint program;
	std::string readShader(std::string fileName);
	void loadShader(GLint type, std::string fileName, GLuint& shaderProgram);
public:
	GLuint getProgram();
	Shader();
	~Shader();
};
