#pragma once
#include "Renderable2D.h"
#include <vector>

namespace core { namespace graphics {

	#define RENDERER_MAX_SPRITES		60000
	#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
	#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4 
	#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
	#define RENDERER_MAX_INDEX_COUNT	RENDERER_MAX_SPRITES * 6

	#define VERTEX_POSITION_ATTRIB 0
	#define VERTEX_COLOR_ATTRIB    1
	//TODO: extend to support other data later

	struct VertexData {
		glm::vec4 position;
		unsigned int color;
	};

	class Renderer2D {
	protected:

		std::vector<glm::mat4> m_TransformationStack;
		glm::mat4* m_StackTop;

	protected:

		Renderer2D()
		{
			//push the identity matrix onto the transformation stack
			m_TransformationStack.push_back(glm::mat4(1.0));
			m_StackTop = &m_TransformationStack.back();
		}

	public:

		void push(const glm::mat4& matrix, bool override = false)
		{

			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back((*m_StackTop * matrix));
			m_StackTop = &m_TransformationStack.back();
		}

		void pop()
		{
			if (m_TransformationStack.size() > 1) {
				m_TransformationStack.pop_back();
				m_StackTop = &m_TransformationStack.back();
			}
		}

		virtual void begin() = 0;
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void flush() = 0;
		virtual void end() = 0;

	};

 } }