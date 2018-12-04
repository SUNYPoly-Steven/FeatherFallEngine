#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace core { namespace math {
   
    static float toRads(float degrees) {
        return (float)(degrees * (M_PI / 180));
    }
    
} }