#include <GL/glew.h>
#include "VBO.h"
#include "../debuging.h"

namespace core { namespace buffers {

	VBO::VBO(const void* data, unsigned int size, bool staticDraw /* = true*/) {
		GLCall(glGenBuffers(1, &vboID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, (staticDraw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
	}

	VBO::~VBO() {
		GLCall(glDeleteBuffers(1, &vboID));
	}

	void VBO::bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	}

	void VBO::unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

} }