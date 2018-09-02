#pragma once
#include "Renderable3D.h"

namespace core { namespace graphics {

	class Renderer3D {
	private:



	protected:

		Renderer3D()
		{
		}

		virtual ~Renderer3D() 
		{
		}

	public:

		virtual void begin() = 0;
		virtual void submit(const Renderable3D* renderable) = 0;
		virtual void flush() = 0;
		virtual void end() = 0;

	};

}}