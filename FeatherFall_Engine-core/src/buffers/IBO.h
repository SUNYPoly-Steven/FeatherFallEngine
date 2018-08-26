#pragma once

namespace core { namespace buffers {

	class IBO {
	private:

		unsigned int iboID;
		unsigned int count;

	public:

		IBO(const unsigned int* pdata, unsigned int pcount, bool staticDraw = true);
		~IBO();

		/*BINDS the IBO*/
		void bind() const ;

		/*UNBINDS the IBO*/
		void unbind() const ;

		inline int getCount() const { return count; }

	private:



	};

} }