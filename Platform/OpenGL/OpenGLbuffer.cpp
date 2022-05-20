#include "OpenGLBuffer.h"
#include <vector>

using namespace MotionNinis;


VertexBufferObject::VertexBufferObject(std::vector<GLfloat> data) {
	glGenBuffers(1, &buffer_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_renderID);
	glBufferData(GL_ARRAY_BUFFER, data.size(), &data, GL_STATIC_DRAW);
}
VertexBufferObject::~VertexBufferObject() {
	glDeleteBuffers(1, &buffer_renderID);
}



GLuint MotionNinis::VertexBufferObject::BindAndSetDataVertexBufferObject(GLuint VertexBuffer, std::vector<GLfloat> data) {
	
	return VertexBuffer;
}





// vertex array

MotionNinis::VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &ArrayObject_renderID);
	glBindVertexArray(ArrayObject_renderID);
}
MotionNinis::VertexArrayObject::~VertexArrayObject() {
	glDeleteVertexArrays(1, &ArrayObject_renderID);
}




// EBO
MotionNinis::ElementArrayBuffer::ElementArrayBuffer(std::vector<GLfloat> data){
	glGenBuffers(1, &buffer_renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size(), &data, GL_STATIC_DRAW);
}
MotionNinis::ElementArrayBuffer::~ElementArrayBuffer() {
	glDeleteBuffers(1, &buffer_renderID);
}