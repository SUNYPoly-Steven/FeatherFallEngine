#pragma once
#include "../buffers/VAO.h"
#include "../buffers/VBO.h"
#include "../buffers/IBO.h"
#include "../buffers/BufferLayout.h"
#include <glm/vec3.hpp>


namespace core { namespace graphics {

	class Renderable3D {
	public:

		buffers::VAO vao; //there HAS to be a better way to make renderables with a VAO for each one...
		buffers::VBO vbo;
		buffers::IBO ibo;

	public:

		Renderable3D() 
			: vbo(nullptr, 0), ibo(nullptr, 0) 
		{
		}

		Renderable3D(const void* vertData, const unsigned int* indexData, unsigned int vertexSize, unsigned int indexSize, bool staticDraw = true)
			: vbo(vertData, vertexSize, staticDraw), ibo(indexData, indexSize, staticDraw)
		{
			buffers::BufferLayout layout = buffers::BufferLayout();
			layout.push<float>(3); //position
			layout.push<float>(4); //color

			vao.addBuffer(vbo, layout);
		}


	private:



	};

} }
