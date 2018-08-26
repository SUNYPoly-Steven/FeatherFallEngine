#include <GL/glew.h>
#include "VAO.h"
#include "../debuging.h"

namespace core { namespace buffers {

	VAO::VAO() {
		GLCall(glGenVertexArrays(1, &vaoID));
	}

	VAO::~VAO() {
		GLCall(glDeleteVertexArrays(1, &vaoID));
	}

	void VAO::bind() const {
		GLCall(glBindVertexArray(vaoID));
	}

	void VAO::unbind() const {
		GLCall(glBindVertexArray(0));
	}

	void VAO::addBuffer(const VBO& vb, const BufferLayout& layout) {
		
		bind();
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); ++i) {
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));

			offset += element.count * GLsizeof(element.type);

		}

	}

} }