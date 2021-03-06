#include "glmAnimation3D.h"
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Editor/imgui/imgui.h"
#include "Editor/imgui/imgui_impl_glfw.h"
#include "Editor/imgui/imgui_impl_opengl3.h"
#include "Editor/imgui/imgui_internal.h"
#include "Editor/UserInterface.h"

float angle = 20;
int a = 0;
std::vector<glm::vec3> CubeVertecices = {
		glm::vec3(0.6, 1.0, 0.3),
		glm::vec3(0.6, 1.0, 0.9),
		glm::vec3(0.3, 1.0, 0.4),
		glm::vec3(0.6, 0.1, 0.9),
		glm::vec3(0.2, 0.3, 0.2),
		glm::vec3(0.7, 1.0, 0.9),
		glm::vec3(0.6, 1.0, 0.3),
		glm::vec3(0.6, 1.0, 0.9),
		glm::vec3(0.3, 1.0, 0.4),
		glm::vec3(0.6, 0.1, 0.9),
		glm::vec3(0.2, 0.3, 0.2),
		glm::vec3(0.7, 1.0, 0.9),glm::vec3(0.6, 1.0, 0.3),
		glm::vec3(0.6, 1.0, 0.9),
		glm::vec3(0.3, 1.0, 0.4),
		glm::vec3(0.6, 0.1, 0.9),
		glm::vec3(0.2, 0.3, 0.2),

};
glmAnimation3D::glmAnimation3D(GLFWwindow* window) {
	projectionPerspective; view; model; transform; size; size2; Scale2; LastedFloatFrameX = 1.0f;
	LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f;
}
glmAnimation3D::~glmAnimation3D() {}
void glmAnimation3D::setMatrixPerspectiveProjection(float& FOV, float& width, float& height, Camera camera) {
	projectionPerspective = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 1000.0f);
}
void glmAnimation3D::setModelProjection(float& ValueRotate) {
	model = glm::rotate(model, glm::radians(ValueRotate), glm::vec3(0.1f, 0.1f, 0.1f));
}
void glmAnimation3D::setViewProjection() {
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}
void glmAnimation3D::setTransformValue() {
	transform = glm::translate(transform, glm::vec3(0.0f, 1.0f, -0.5f));
}
void glmAnimation3D::frameMatrix(GLuint& shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view)); // frame view matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model)); // frame model matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projectionPerspective)); // frame projectionPerspective matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform)); // frame transform matrix variable
}
void glmAnimation3D::setRotateRight(float& Radius) {
	transform = glm::rotate(transform, glm::radians(Radius), glm::vec3(-0.5f, 0.0f, 0.0f));
}
void glmAnimation3D::setRotateLeft(float Radius, float& ValueX, float& ValueY, float& ValueZ) {
	if (ValueX > -1 || ValueY > -1 || ValueZ > -1) {
		transform = glm::rotate(transform, glm::radians(Radius), glm::vec3(ValueX, ValueY, ValueZ));
	}
	else if (ValueX == 0 || ValueY == 0 || ValueZ == 0) {
		transform = glm::rotate(transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else {
		transform = glm::rotate(transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
}
void glmAnimation3D::drawAnimation(GLuint shader, Render render, objectUser::Mesh mesh, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
	mesh.activeTexture();

	for (int i(0); i < CubeVertecices.size(); i++) {
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		transform = glm::translate(transform, CubeVertecices[i]);
		transform = glm::rotate(transform, glm::radians(angle * i), glm::vec3(1.0f, 0.3f, 0.5f));
		this->frameMatrix(shader);
		this->setLookAtMatrixCamera(camPos, camFront, camUp);

		mesh.drawMesh(); // in this fonction they are the actives textures
	}
}
void glmAnimation3D::initialiseMatrix() {
	model = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
	projectionPerspective = glm::mat4(1.0f);
}
float glmAnimation3D::setColorValueFrame() {
	float color = 0;
	ImGui::ColorEdit4(" Color Frame ", &color);
	if (color > -401602080) {
		return color;
	}
	else {
		return 0.0f;
	}
}
void glmAnimation3D::setColorObject(GLuint& shader, float ValueR, float ValueG, float ValueB) {
	glUniform1f(glGetUniformLocation(shader, "ColorR"), ValueR);
	glUniform1f(glGetUniformLocation(shader, "ColorG"), ValueG);
	glUniform1f(glGetUniformLocation(shader, "ColorB"), ValueB);
}
void glmAnimation3D::setPositionObject(GLuint& shader, float ValueX, float ValueY, float ValueZ) {
	glUniform1f(glGetUniformLocation(shader, "PositionX"), ValueX);
	glUniform1f(glGetUniformLocation(shader, "PositionY"), ValueY);
	glUniform1f(glGetUniformLocation(shader, "PositionZ"), ValueZ);
}
void glmAnimation3D::setPercentTexture(GLuint& shader, float Value) {
	glUniform1f(glGetUniformLocation(shader, "PercentTexture"), Value);
}
void glmAnimation3D::setLookAtMatrixCamera(glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
	view = glm::lookAt(camPos, camPos + camFront, camUp);
}
float glmAnimation3D::getValueX() { return LastedFloatFrameX; }
float glmAnimation3D::getValueY() { return LastedFloatFrameY; }
float glmAnimation3D::getValueZ() { return LastedFloatFrameZ; }
glm::mat4 glmAnimation3D::getmodelVARIABLE() { return model; }
glm::mat4 glmAnimation3D::getviewVARIABLE() { return view; }
glm::mat4 glmAnimation3D::gettransformVARIABLE() { return transform; }
glm::mat4 glmAnimation3D::getprojectionPerspectiveVARIABLE() { return projectionPerspective; }




// variables size
 






float VariablesSize::KoefMultiplicatorSizeALL = static_cast<float>(1.0f);
float VariablesSize::LastedFloatFrame[] = { 1.0f };

VariablesSize::VariablesSize(GLFWwindow* window) : AnimationProgramUser(window) {
	SizeMatrix = glm::scale(SizeMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
	LastedFloatFrame[0] = 1.0f;
	LastedFloatFrame[1] = 1.0f;
	LastedFloatFrame[2] = 1.0f;

}
VariablesSize::~VariablesSize() {}

void VariablesSize::InputSize() {
	ImGui::InputFloat3("input:X,Y,Z", LastedFloatFrame);
}
void VariablesSize::setCHANGE_VALUE_ALL_SIZE(GLuint& shader, int Value) { // this fonction save the 3 axes (X, Y, Z)
	SizeMatrix = glm::mat4(1.0f);
	if (Value == IN_FRAME_NOT) {
		ImGui::SliderFloat("sizeALL", &this->KoefMultiplicatorSizeALL, -10, 10);
	}
	SizeMatrix = glm::scale(SizeMatrix, glm::vec3(this->LastedFloatFrame[0] * this->KoefMultiplicatorSizeALL,
		this->LastedFloatFrame[1] * this->KoefMultiplicatorSizeALL,
		this->LastedFloatFrame[2] * this->KoefMultiplicatorSizeALL));
	glUniformMatrix4fv(glGetUniformLocation(shader, "Scale"), 1, GL_FALSE, glm::value_ptr(SizeMatrix));

}
void VariablesSize::setCHANGE_X(int ValueIndicator) {
	if (ValueIndicator == IN_FRAME_NOT) {
		ImGui::SliderFloat("sizeX", &this->LastedFloatFrame[0], -this->LastedFloatFrame[0] - 100, this->LastedFloatFrame[0] + 100);
	}
}
void VariablesSize::setCHANGE_Y(int ValueIndicator) {
	if (ValueIndicator == IN_FRAME_NOT) {
		ImGui::SliderFloat("sizeY", &this->LastedFloatFrame[1], -this->LastedFloatFrame[1] - 100, this->LastedFloatFrame[1] + 100);
	}
}
void VariablesSize::setCHANGE_Z(int ValueIndicator) {
	if (ValueIndicator == IN_FRAME_NOT) {
		ImGui::SliderFloat("sizeZ", &this->LastedFloatFrame[2], -this->LastedFloatFrame[2] - 100, this->LastedFloatFrame[2] + 100);
	}
}





// position class
VariablePosition::VariablePosition(GLFWwindow* window) : AnimationProgramUser(window) {}
VariablePosition::~VariablePosition() {}

void VariablePosition::setCHANGE_X(int ValueIndicator) {

}
void VariablePosition::setCHANGE_Y(int ValueIndicator) {

}
void VariablePosition::setCHANGE_Z(int ValueIndicator) {

}



// rotate class 
RotateAxes::RotateAxes(GLFWwindow* window) : AnimationProgramUser(window) {

}
RotateAxes::~RotateAxes() {}

void RotateAxes::setCHANGE_X(int ValueIndicator) {

}
void RotateAxes::setCHANGE_Y(int ValueIndicator) {

}
void RotateAxes::setCHANGE_Z(int ValueIndicator) {

}





// color class


Color::Color() { 
	LastedFloatFrameColor;
	LastedFloatObjectColor;
}
Color::~Color() {}



 // AnimationProgramUser class

AnimationProgramUser::AnimationProgramUser(GLFWwindow* window) {

}
AnimationProgramUser::~AnimationProgramUser() {}