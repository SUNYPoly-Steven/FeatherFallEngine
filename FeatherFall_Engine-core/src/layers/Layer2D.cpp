#include "Layer2D.h"
#include "../logging/Logging.h"

namespace core {


	Layer2D::Layer2D()
		: Layer(new graphics::BatchRenderer2D())
	{
	}
	
	Layer2D::~Layer2D()
	{	
	}


}