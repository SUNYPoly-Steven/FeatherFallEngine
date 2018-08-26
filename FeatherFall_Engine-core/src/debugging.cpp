#include <iostream>
#include "FeatherFall-gl.h"

bool GLLogError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] ( " << error << " ) \n" << file << "\n" << line << ": " << function << std::endl << std::endl;
		return false;
	}
	return true;
}

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}