#ifndef DEF_GLMANIMATION3D
#define DEF_GLMANIMATION3D

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"
#include <glm/gtc/type_ptr.hpp>

// the fonction of this class is animate de 3d objects and set the matrix projection of the engine
class glmAnimation3D : public cube
{
public:
	glmAnimation3D();
	~glmAnimation3D();
	void initialiseMatrix();
	void setModelProjection();
	void setViewProjection();
	void setMatrixPerspectiveProjection(float FOV, float& width, float& height);
	void frameMatrix(GLuint shader);
	void setTransformValue();
	void setRotateRight(float Radius);
	void setRotateLeft(float Radius);
	glm::mat4 setScaleValue(GLuint shader, float Value);
	glm::mat4 setScaleValueX(GLuint shader, float Value);
	glm::mat4 setScaleValueY(GLuint shader, float Value);
	glm::mat4 setScaleValueZ(GLuint shader, float Value);
	glm::mat4 getprojectionPerspectiveVARIABLE();
	glm::mat4 getviewVARIABLE();
	glm::mat4 getmodelVARIABLE();
	glm::mat4 gettransformVARIABLE();
protected:
	glm::mat4 projectionPerspective;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 transform;
	glm::mat4 size;
};

#endif // !1
