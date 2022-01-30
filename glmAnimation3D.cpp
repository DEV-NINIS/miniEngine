#include "glmAnimation3D.h"
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glmAnimation3D::glmAnimation3D(GLFWwindow* window)  {
	cube();
	projectionPerspective; view; model; transform; size; size2; Scale2;
}
glmAnimation3D::~glmAnimation3D() {}
void glmAnimation3D::setMatrixPerspectiveProjection(float FOV, float& width, float& height) {
	projectionPerspective = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
}
void glmAnimation3D::setModelProjection() {
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	transform = glm::rotate(transform, glm::radians(Radius), glm::vec3(0.0f, 0.0f, 1.0f));
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
glm::mat4 glmAnimation3D::setScaleValue(GLuint shader, float Value, float ValueX, float ValueY, float ValueZ) {
	size2 = glm::mat4(1.0f);
	if (Value > -401602080) {
		size2 = glm::scale(size2, glm::vec3(Value * ValueX, Value * ValueY, Value * ValueZ));
		glUniformMatrix4fv(glGetUniformLocation(shader, "Scale"), 1, GL_FALSE, glm::value_ptr(size2));
		glUniform1f(glGetUniformLocation(shader, "LastedFrame"), Value);
	}
	return size;
}
float glmAnimation3D::setScaleValueX(GLuint shader, float Value) {
	if (Value > -401602080) {
		glUniform1f(glGetUniformLocation(shader, "LastedFrame"), Value);
		glUniform1f(glGetUniformLocation(shader, "scaleX"), Value);
		return Value;
	}
	else { return 1.0f; }
}
float glmAnimation3D::setScaleValueY(GLuint shader, float Value) {
	if (Value > -401602080) {
		glUniform1f(glGetUniformLocation(shader, "LastedFrame"), Value);
		glUniform1f(glGetUniformLocation(shader, "scaleY"), Value);
		return Value;
	}
	else { return 1.0f; }

}
float glmAnimation3D::setScaleValueZ(GLuint shader, float Value) {
	if (Value > -401602080) {
		glUniform1f(glGetUniformLocation(shader, "LastedFrame"), Value);
		glUniform1f(glGetUniformLocation(shader, "scaleZ"), Value);
		return Value;
	}
	else { return 1.0f; }
}
void glmAnimation3D::linkMatrix(GLuint shader, float ValueX, float ValueY, float ValueZ) {
	Scale2 = glm::mat4(1.0f);
	Scale2 = glm::translate(Scale2, glm::vec3(ValueX, ValueY, ValueZ));
	glUniformMatrix4fv(glGetUniformLocation(shader, "Scale2"), 1, GL_FALSE, glm::value_ptr(Scale2));
}
glm::mat4 glmAnimation3D::getmodelVARIABLE() { return model; }
glm::mat4 glmAnimation3D::getviewVARIABLE() { return view; }
glm::mat4 glmAnimation3D::gettransformVARIABLE() { return transform; }
glm::mat4 glmAnimation3D::getprojectionPerspectiveVARIABLE() { return projectionPerspective; }