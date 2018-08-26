#pragma once

namespace core { namespace buffers {

	class VBO {
	private:
	
		unsigned int vboID;

	public:

		VBO(const void* data, unsigned int size, bool staticDraw = true);
		~VBO();

		/*BINDS the VBO*/
		void bind() const ;

		/*UNBINDS the VBO*/
		void unbind() const ;

	private:



	};

} }