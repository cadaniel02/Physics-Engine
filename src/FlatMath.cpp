#include "../include/FlatMath.h"
#include <cmath>

namespace FlatPhysics{

    float FlatMath::clamp(float val, float min, float max){
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    float FlatMath::length(const FlatVector& v){
        return std::sqrtf(v.x()*v.x() + v.y()*v.y());
    }

    float FlatMath::lengthSquared(const FlatVector& v){
        return v.x()*v.x() + v.y()*v.y();
    }

    float FlatMath::distance(const FlatVector& v1, const FlatVector& v2){
        return std::sqrtf((v1.x()-v2.x())*(v1.x()-v2.x()) + (v1.y()-v2.y())*(v1.y()-v2.y()));
    }

    float FlatMath::distanceSquared(const FlatVector& v1, const FlatVector& v2){
        return (v1.x()-v2.x())*(v1.x()-v2.x()) + (v1.y()-v2.y())*(v1.y()-v2.y());
    }

    FlatVector FlatMath::normalize(const FlatVector& v){
        return v / length(v);
    }

    float dot(const FlatVector& v1, const FlatVector& v2){
        return (v1.x() * v2.x()) + (v1.y() * v2.y());
    }
            
    float cross(const FlatVector&, const FlatVector&){
        return 0;
    }

}