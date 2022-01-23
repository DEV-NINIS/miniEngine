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
	view = glm::translate(view, glm::vec3(1.0f, 0.0f, -3.0f));
}
void glmAnimation3D::frameMatrix(GLuint shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(this->getviewVARIABLE())); // frame view matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(this->getmodelVARIABLE())); // frame model matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(this->getprojectionPerspectiveVARIABLE())); // frame projectionPerspective matrix variable
	glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(this->gettransformVARIABLE())); // frame transform matrix variable
}
void glmAnimation3D::initialiseMatrix() {
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
	projectionPerspective = glm::mat4(1.0f);
}
glm::mat4 glmAnimation3D::getmodelVARIABLE() { return model; }
glm::mat4 glmAnimation3D::getviewVARIABLE() { return view; }
glm::mat4 glmAnimation3D::gettransformVARIABLE() { return transform; }
glm::mat4 glmAnimation3D::getprojectionPerspectiveVARIABLE() { return projectionPerspective; }