#include "Sprite.h"

namespace core { namespace graphics {

	Sprite::Sprite(float px, float py, float pwidth, float pheight, const glm::vec4 & pcolor)
		: Renderable2D(glm::vec4(px, py, 0.0f, 1.0f), glm::vec2(pwidth, pheight), pcolor)
	{
	}


} }
