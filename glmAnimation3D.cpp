#include "glmAnimation3D.h"
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include "UserInterface.h"


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
void glmAnimation3D::setMatrixPerspectiveProjection(float& FOV, float& width, float& height) {
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
void glmAnimation3D::initialiseMatrix() {
	model = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
	projectionPerspective = glm::mat4(1.0f);
}
glm::mat4 glmAnimation3D::setScaleValue(GLuint& shader, float& Value) {
	size2 = glm::mat4(1.0f);
	if (Value > -401602080) {
		size2 = glm::scale(size2, glm::vec3(Value * 1.0f * this->LastedFloatFrameX, Value * 1.0f * this->LastedFloatFrameY, Value * 1.0f * this->LastedFloatFrameZ));
		glUniformMatrix4fv(glGetUniformLocation(shader, "Scale"), 1, GL_FALSE, glm::value_ptr(size2));
	}
	return size;
}
float glmAnimation3D::setScaleValueX(GLuint& shader) {
		float* size2 = nullptr; size2 = new float;
		ImGui::SliderFloat("sizeX", &*size2, -2, 3);
		if (*size2 > -401602080) {
			LastedFloatFrameX = *size2;
			return *size2;
		}
		else {
			return LastedFloatFrameX;
		}
		delete size2;
}
float glmAnimation3D::setScaleValueY(GLuint& shader) {
	float* size3 = nullptr; size3 = new float;
	ImGui::SliderFloat("sizeY", &*size3, -5, 5);
	if (*size3 > -401602080) {
		LastedFloatFrameY = *size3;
		return *size3;
	}
	else {
		return LastedFloatFrameY;
	}
	delete size3;
}
float glmAnimation3D::setScaleValueZ(GLuint& shader) {
	float* size4 = nullptr; size4 = new float;
	ImGui::SliderFloat("sizeZ", &*size4, -5, 5);
	if (*size4 > -401602080) {
		LastedFloatFrameZ = *size4;
		return *size4;
	}
	else {
		return LastedFloatFrameZ;
	}
	delete size4;
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
	view = glm::lookAt(camPos, camPos - camFront, camUp);
}
float glmAnimation3D::getValueX() { return LastedFloatFrameX; }
float glmAnimation3D::getValueY() { return LastedFloatFrameY; }
float glmAnimation3D::getValueZ() { return LastedFloatFrameZ; }
glm::mat4 glmAnimation3D::getmodelVARIABLE() { return model; }
glm::mat4 glmAnimation3D::getviewVARIABLE() { return view; }
glm::mat4 glmAnimation3D::gettransformVARIABLE() { return transform; }
glm::mat4 glmAnimation3D::getprojectionPerspectiveVARIABLE() { return projectionPerspective; }