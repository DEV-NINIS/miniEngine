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
#include "UserInterface.h"

// the fonction of this class is animate de 3d objects and set the matrix projection of the engine
class glmAnimation3D : public cube
{
public:
	glmAnimation3D(GLFWwindow* window);
	virtual ~glmAnimation3D();
	void initialiseMatrix();
	void setModelProjection(float ValueRotate);
	void setViewProjection();
	void setMatrixPerspectiveProjection(float FOV, float& width, float& height);
	void frameMatrix(GLuint shader);
	void setTransformValue();
	void setRotateRight(float Radius);
	void setRotateLeft(float Radius);
	void linkMatrix(GLuint shader, float ValueX, float ValueY, float ValueZ);
	glm::mat4 setScaleValue(GLuint shader, float Value);
	float setColorValueFrame();
	float setScaleValueX(GLuint shader);
	float setScaleValueY(GLuint shader);
	float setScaleValueZ(GLuint shader);
	float getValueX(); float getValueY(); float getValueZ();
	glm::mat4 getprojectionPerspectiveVARIABLE();
	glm::mat4 getviewVARIABLE();
	glm::mat4 getmodelVARIABLE();
	glm::mat4 gettransformVARIABLE();
	
protected:
	float LastedFloatFrameX;
	float LastedFloatFrameY;
	float LastedFloatFrameZ;
	glm::mat4 projectionPerspective;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 transform;
	glm::mat4 size;
	glm::mat4 size2;
	glm::mat4 Scale2;
};

#endif // !1
