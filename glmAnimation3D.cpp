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

glmAnimation3D::glmAnimation3D(GLFWwindow* window) {
	projectionPerspective; view; model; transform; size; size2; Scale2; LastedFloatFrameX = 1.0f;
	LastedFloatFrameY = 1.0f; LastedFloatFrameZ = 1.0f;
}
glmAnimation3D::~glmAnimation3D() {}
void glmAnimation3D::setMatrixPerspectiveProjection(float FOV, float& width, float& height) {
	projectionPerspective = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
}
void glmAnimation3D::setModelProjection() {
	model = glm::rotate(model, glm::radians(180.0f * static_cast<float>(sin(glfwGetTime()))), glm::vec3(1.0f, 0.5f, 0.0f));
}
void glmAnimation3D::setViewProjection() {
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}
void glmAnimation3D::setTransformValue() {
	transform = glm::translate(transform, glm::vec3(sin(0.0f), 1.0f, -0.5f));
}
void glmAnimation3D::frameMatrix(GLuint shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view)); // frame view matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model)); // frame model matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projectionPerspective)); // frame projectionPerspective matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform)); // frame transform matrix variable
}
void glmAnimation3D::setRotateRight(float Radius) {
	transform = glm::rotate(transform, glm::radians(static_cast<float>(sin(glfwGetTime()))), glm::vec3(0.0f, 0.0f, 1.0f));
}
void glmAnimation3D::setRotateLeft(float Radius) {
	transform = glm::rotate(transform, glm::radians(Radius), glm::vec3(0.0f, 0.0f, -1.0f));
}
void glmAnimation3D::initialiseMatrix() {
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
	projectionPerspective = glm::mat4(1.0f);
}
glm::mat4 glmAnimation3D::setScaleValue(GLuint shader, float Value) {
	size2 = glm::mat4(1.0f);
	if (Value > -401602080) {
		size2 = glm::scale(size2, glm::vec3(Value * 1.0f * this->LastedFloatFrameX, Value * 1.0f * this->LastedFloatFrameY, Value * 1.0f * this->LastedFloatFrameZ));
		glUniformMatrix4fv(glGetUniformLocation(shader, "Scale"), 1, GL_FALSE, glm::value_ptr(size2));
		glUniform1f(glGetUniformLocation(shader, "LastedFrame"), Value);
	}
	return size;
}
float glmAnimation3D::setScaleValueX(GLuint shader) {
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
		glUniform1f(glGetUniformLocation(shader, "LastedFrame"), LastedFloatFrameX);
		glUniform1f(glGetUniformLocation(shader, "scaleX"), LastedFloatFrameX);
}
float glmAnimation3D::setScaleValueY(GLuint shader) {
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
	glUniform1f(glGetUniformLocation(shader, "LastedFrame"), LastedFloatFrameY);
	glUniform1f(glGetUniformLocation(shader, "scaleY"), LastedFloatFrameY);
}
float glmAnimation3D::setScaleValueZ(GLuint shader) {
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
	glUniform1f(glGetUniformLocation(shader, "LastedFrame"), LastedFloatFrameZ);
	glUniform1f(glGetUniformLocation(shader, "scaleZ"), LastedFloatFrameZ);
}
void glmAnimation3D::linkMatrix(GLuint shader, float ValueX, float ValueY, float ValueZ) {
	Scale2 = glm::mat4(1.0f);
	Scale2 = glm::translate(Scale2, glm::vec3(ValueX, ValueY, ValueZ));
	glUniformMatrix4fv(glGetUniformLocation(shader, "Scale2"), 1, GL_FALSE, glm::value_ptr(Scale2));
}
float glmAnimation3D::setColorValueFrame() {
	float* color = 0; color = new float; *color = 0;
	ImGui::ColorEdit4(" Color Frame ", &*color);
	if (*color > -401602080) {
		return *color;
	}
	delete color;
}
float glmAnimation3D::getValueX() { return LastedFloatFrameX; }
float glmAnimation3D::getValueY() { return LastedFloatFrameY; }
float glmAnimation3D::getValueZ() { return LastedFloatFrameZ; }
glm::mat4 glmAnimation3D::getmodelVARIABLE() { return model; }
glm::mat4 glmAnimation3D::getviewVARIABLE() { return view; }
glm::mat4 glmAnimation3D::gettransformVARIABLE() { return transform; }
glm::mat4 glmAnimation3D::getprojectionPerspectiveVARIABLE() { return projectionPerspective; }