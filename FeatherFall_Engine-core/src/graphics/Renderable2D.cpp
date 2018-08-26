#include "Renderable2D.h"

namespace core { namespace graphics {

	Renderable2D::Renderable2D(const glm::vec4& pposition, const glm::vec2& psize, const glm::vec4& pcolor)
		: position(pposition), size(psize), color(pcolor)
	{
	}

	Renderable2D::Renderable2D(float px, float py, float sizex, float sizey, unsigned int pcolor)
		: position(px, py, 0.0f, 1.0f), size(sizex, sizey)
	{

		unsigned int rmask = 0xFF000000; // 1's in the largest byte
		unsigned int gmask = 0x00FF0000; // 1's in the third byte
		unsigned int bmask = 0x0000FF00; // 1's in the second byte
		unsigned int amask = 0x000000FF; // 1's in the smallest byte

		color.r = (float)((pcolor & rmask) >> 24);
		color.g = (float)((pcolor & gmask) >> 16);
		color.b = (float)((pcolor & bmask) >> 8);
		color.a = (float)((pcolor & amask) >> 0);

		color /= 255.0f; // normalize color to be between 0 - 1

	}

	Renderable2D::~Renderable2D() { }

} }