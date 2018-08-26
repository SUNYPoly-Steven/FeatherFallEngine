#include <GL\glew.h>
#include "IBO.h"
#include "..\debuging.h"

namespace core { namespace buffers {

	IBO::IBO(const unsigned int* pdata, unsigned int pcount, bool staticDraw /*= true*/)
		:count(pcount)
	{
		GLCall(glGenBuffers(1, &iboID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
#if _DEBUG	//this will make sure that unsigned int 
			//is equal to GLuint and will break if its not
		FF_ASSERT(sizeof(unsigned int) == sizeof(GLuint));
#endif
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), pdata, (staticDraw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
	}

	IBO::~IBO() {
		GLCall(glDeleteBuffers(1, &iboID));
	}

	void IBO::bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
	}

	void IBO::unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

} }