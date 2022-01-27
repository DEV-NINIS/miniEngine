#include "glmAnimation3D.h"
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glmAnimation3D::glmAnimation3D() : cube() {
	projectionPerspective; view; model; transform; 
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
glm::mat4 glmAnimation3D::setScaleValue(GLuint shader, float Value) {
	glm::mat4 size = glm::mat4(1.0f);
	size = glm::scale(size, glm::vec3(Value, Value, Value));
	glUniformMatrix4fv(glGetUniformLocation(shader, "Scale"), 1, GL_FALSE, glm::value_ptr(size));
	return size;
}
glm::mat4 glmAnimation3D::getmodelVARIABLE() { return model; }
glm::mat4 glmAnimation3D::getviewVARIABLE() { return view; }
glm::mat4 glmAnimation3D::gettransformVARIABLE() { return transform; }
glm::mat4 glmAnimation3D::getprojectionPerspectiveVARIABLE() { return projectionPerspective; }