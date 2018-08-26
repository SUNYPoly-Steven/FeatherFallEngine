#include "Layer.h"
#include "../logging/Logging.h"

namespace core {


	Layer::Layer(graphics::Renderer2D* renderer)
		: m_Renderer(renderer)
	{

	}

	Layer::~Layer()
	{
		delete m_Renderer;

		for (auto& renderable : m_Renderables)
			delete renderable;

	}

	void Layer::add(graphics::Renderable2D* renderable) 
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::render() 
	{
	
		m_Renderer->begin();

		for (auto& renderable : m_Renderables) {
			m_Renderer->submit(renderable);
		}

		m_Renderer->end();

		m_Renderer->flush();

		

	}


}