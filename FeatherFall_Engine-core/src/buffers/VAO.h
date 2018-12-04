#pragma once

#include "VBO.h"
#include "BufferLayout.h"

namespace core { namespace buffers {

	class VAO {
	private:

		unsigned int vaoID;

	public:

		VAO();
		~VAO();

		/* BINDS the VAO */
		void bind() const ;

		/* UNBINDS the VAO */
		void unbind() const ;

		void addBuffer(const VBO& vb, const BufferLayout& layout);

	private:



	};

} }