#pragma once

#include <vector>
#include <GL/glew.h>
#include "../debuging.h"

namespace core { namespace buffers {
	
	struct BufferElement {

		unsigned int type;
		unsigned int count;
		unsigned int normalized;

		static unsigned int SizeOfType(unsigned int type) {
			switch (type) {
			case GL_FLOAT:
				return sizeof(GLfloat);

			case GL_UNSIGNED_INT:
				return sizeof(GLuint);

			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
			}

			FF_ASSERT(false);
			return 0;

		}

	};
	#define GLsizeof(x) BufferElement::SizeOfType(x)

	class BufferLayout {
	private:

		std::vector<BufferElement> elements;
		unsigned int stride;

	public:

		BufferLayout()
			: stride(0)
		{
		}

		template<typename T>
		void push(unsigned int count) 
		{
			//if an unsupported type is used, 
			//this will create a compile time error
			static_assert(false, 
				"Unsupported type for BufferLayout::push<typename T>(unsigned int)");
		}

		template<>
		void push<float>(unsigned int count) 
		{
			elements.push_back({ GL_FLOAT, count, GL_FALSE });
			stride += count * GLsizeof(GL_FLOAT);
		}

		template<>
		void push<unsigned int>(unsigned int count) 
		{
			elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			stride += count * GLsizeof(GL_UNSIGNED_INT);
		}

		template<>
		void push<unsigned char>(unsigned int count) 
		{
			elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			stride += count * GLsizeof(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<BufferElement>& getElements() const { return elements; }
		inline unsigned int getStride() const { return stride; }

	private:



	};

} }