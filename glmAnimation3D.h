#ifndef DEF_GLMANIMATION3D
#define DEF_GLMANIMATION3D

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "object.h"
#include <glm/gtc/type_ptr.hpp>
#include "UserInterface.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define ADD_NODE_ROTATE_RIGHT 1
#define ADD_NODE_ROTATE_LEFT 2
#define ADD_NODE_MOVE_CAMERA_LEFT 3
#define ADD_NODE_MOVE_CAMERA_RIGHT 4
#define ADD_NODE_MOVE_CAMERA_UP 5
#define ADD_NODE_MOVE_CAMERA_DOWN 6
#define ADD_NODE_ROTATE_AROUD_X_MATRIX 7
#define ADD_NODE_ROTATE_AROUND_Y_MATRIX 8
#define ADD_NODE_ROTATE_AROUND_Z_MATRIX 9
#define ADD_NODE_CHANGE_CAMERA_SPEED 10
#define ADD_NODE_CHANGE_PERCENT_TEXTURE 11
#define ADD_NODE_CHANGE_POSITION_X 12
#define ADD_NODE_CHANGE_POSITION_Y 13
#define ADD_NODE_CHANGE_POSITION_Z 14
#define ADD_NODE_CHANGE_COLOR_FRAME 15
#define ADD_NODE_CHANGE_COLOR_OBJECT 16
#define ADD_NODE_CHANGE_FOV 17
#define ADD_NODE_CHANGE_SIZE_X 18 
#define ADD_NODE_CHANGE_SIZE_Y 19
#define ADD_NODE_CHANGE_SIZE_Z 20
#define ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX 21

	
#include "glmAnimation3D.inl"

// the fonction of this class is animate de 3d objects and set the matrix projection of the engine


template<typename T> inline T setCHANGE_DIRECTION_ROTATE_MATRIX();
template<typename T> inline T setADD_NODE_CHANGE_FOV();
template<typename T> inline T setCHANGE_COLOR_OBJECT();
template<typename T> inline T setCHANGE_COLOR_FRAME();
template<typename T> inline T setCHANGE_POSITION_Z();
template<typename T> inline T setCHANGE_POSITION_Y();
template<typename T> inline T setCHANGE_POSITION_X();
template<typename T> inline T setCHANGE_PERCENT_TEXTURE();
template<typename T> inline T setCHANGE_CAMERA_SPEED();
template<typename T> inline T setROTATE_AROUND_Z_MATRIX();
template<typename T> inline T setROTATE_AROUND_Y_MATRIX();
template<typename T> inline T setROTATE_AROUD_X_MATRIX();
template<typename T> inline T setMOVE_CAMERA_DOWN();
template<typename T> inline T setMOVE_CAMERA_UP();
template<typename T> inline T setMOVE_CAMERA_RIGHT();
template<typename T> inline T setMOVE_CAMERA_LEFT();



		class VariablesSize {
		public:
			VariablesSize();
			~VariablesSize();
			template<typename U> void setCHANGE_VALUE_ALL_SIZE(GLuint& shader, U& Value) { // this fonction save the 3 axes (X, Y, Z)
				if (this->LastedFloatFrameX != 0 && this->LastedFloatFrameY != 0 && this->LastedFloatFrameZ != 0) {
					SizeMatrix = glm::mat4(1.0f);
					SizeMatrix = glm::scale(SizeMatrix, glm::vec3(this->LastedFloatFrameX,
						this->LastedFloatFrameY,
						this->LastedFloatFrameZ));

					glUniformMatrix4fv(glGetUniformLocation(shader, "Scale"), 1, GL_FALSE, glm::value_ptr(SizeMatrix));
				}
			}
			template<typename T>  T setCHANGE_SIZE_X() {
				ImGui::SliderFloat("sizeX", &this->LastedFloatFrameX, -2, 3);
				if (this->LastedFloatFrameX > -401602080) {
					return this->LastedFloatFrameX;
				}
				else {
					return LastedFloatFrameX;
				}
			}
			template<typename T>  T setCHANGE_SIZE_Y() {
				ImGui::SliderFloat("sizeY", &this->LastedFloatFrameY, -2, 3);
				if (this->LastedFloatFrameY > -401602080) {
					return this->LastedFloatFrameY;
				}
				else {
					return LastedFloatFrameY;
				}
			}
			template<typename T>  T setCHANGE_SIZE_Z() {
				ImGui::SliderFloat("sizeZ", &this->LastedFloatFrameZ, -2, 3);
				if (this->LastedFloatFrameZ > -401602080) {
					return this->LastedFloatFrameZ;
				}
				else {
					return LastedFloatFrameZ;
				}
			}
			static float LastedFloatFrameX;
				static float LastedFloatFrameY;
				static float LastedFloatFrameZ;
		private:
				glm::mat4 SizeMatrix; // this variable have the 3 values of size (axes x, y, z)
		};
// |													|
// |____________________________________________________|
//							|
//					associated variables
//							|
//						   \|/
#include "glmAnimation3D.inl"

			
			

class glmAnimation3D
{
public:
	static glmAnimation3D Ma3d;
	glmAnimation3D(GLFWwindow* window);
	virtual ~glmAnimation3D();
	void initialiseMatrix();
	void setModelProjection(float& ValueRotate);
	void setViewProjection();
	void setMatrixPerspectiveProjection(float& FOV, float& width, float& height, Camera camera);
	void frameMatrix(GLuint& shader);
	void setTransformValue();
	void setRotateRight(float& Radius);
	void setColorObject(GLuint& shader, float ValueR, float ValueG, float ValueB);
	void setPositionObject(GLuint& shader, float ValueX, float ValueY, float ValueZ);
	void setRotateLeft(float Radius, float& ValueX, float& ValueY, float& ValueZ);
	void setLookAtMatrixCamera(glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);
	float setColorValueFrame();
	void setPercentTexture(GLuint& shader, float Value);
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
#endif



	
