#pragma once
#include "../buffers/VAO.h"
#include "../buffers/VBO.h"
#include "../buffers/IBO.h"
#include "../buffers/BufferLayout.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



namespace core { namespace graphics {

	class Renderable3D {
	public:

		buffers::VAO vao; //there HAS to be a better way to make renderables with a VAO for each one...
		buffers::VBO* vbo;
		buffers::IBO* ibo;
		glm::mat4 m_mlMatrix;

	public:

		Renderable3D();

		Renderable3D(const char* filepath);

		Renderable3D(const void* vertData, 
			const unsigned int* indexData, 
			unsigned int vertexSize, 
			unsigned int indexSize, 
			bool staticDraw = true);

		~Renderable3D();


	private:



	};

} }
