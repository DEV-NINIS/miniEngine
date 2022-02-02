
#ifndef DEF_CUBE
#define DEF_CUBE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// cube object
class cube
{
public:
	cube();
	virtual ~cube();
	void setBuffer();
	void setShader();
	void setTexture();
	void useShaderCube();
	void drawElements();
	GLuint getshaderCube();
protected:
	static float vertecies[];
	static unsigned int index[];
	const char* fragmentShaderCODE;
	const char* vertexShaderCODE;
	GLuint VAOcube;
	GLuint VBOcube;
	GLuint EBOcube;
	std::vector<GLuint*> TextureCube;
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint programShader;
	unsigned int tex;
};

#endif // !1

