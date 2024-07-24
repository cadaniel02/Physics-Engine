#ifndef FLAT_MATH_H
#define FLAT_MATH_H

#include "FlatVector.h"

namespace FlatPhysics{

    struct FlatMath{

        static float clamp(float val, float min, float max);

        static float length(const FlatVector&);

        static float lengthSquared(const FlatVector&);

        static float distance(const FlatVector&, const FlatVector&);

        static float distanceSquared(const FlatVector&, const FlatVector&);

        static FlatVector normalize(const FlatVector&);

        static float dot(const FlatVector&, const FlatVector&);
        
        static float cross(const FlatVector&, const FlatVector&);
    };
}

#endif