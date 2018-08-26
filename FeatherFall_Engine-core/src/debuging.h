#pragma once

bool GLLogError(const char* function, const char* file, int line);
void GLClearError();

#ifdef _DEBUG
#    ifdef _MSC_VER
#        define FF_ASSERT(x) if(!(x)) __debugbreak();
#    endif
#endif

#ifndef FF_ASSERT
#    include <cassert>
#    define FF_ASSERT(x) assert(x)
#endif


#ifdef _DEBUG
#    define GLCall(x) GLClearError();\
					  x;\
					  FF_ASSERT(GLLogError(#x, __FILE__, __LINE__))
#else
#    define GLCall(x) x;
#endif

#define SAFE_DELETE(pointer) \
		if (pointer) \
			delete pointer; \
		pointer = 0
