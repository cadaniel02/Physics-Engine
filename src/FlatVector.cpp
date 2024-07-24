#include "../include/FlatVector.h"

namespace FlatPhysics{

    FlatVector::FlatVector(float x, float y) : X(x), Y(y) {}
    FlatVector::FlatVector() : X(0), Y(0) {}

    FlatVector FlatVector::operator+(const FlatVector& v) const {
        return FlatVector(X + v.x(), Y + v.y());
    }

    FlatVector FlatVector::operator-(const FlatVector& v) const {
        return FlatVector(X - v.x(), Y - v.y());
    }

    FlatVector& FlatVector::operator+=(const FlatVector& v) {
        X += v.x();
        Y += v.y();
        return *this;
    }

    FlatVector& FlatVector::operator-=(const FlatVector& v) {
        X -= v.x();
        Y -= v.y();
        return *this;
    }
    
    FlatVector FlatVector::operator-() const {
        return FlatVector(-X, -Y);
    }

    FlatVector FlatVector::operator*(float scalar) const {
        return FlatVector(X * scalar, Y * scalar);
    }
    
    FlatVector FlatVector::operator/(float scalar) const {
        return FlatVector(X / scalar, Y / scalar);
    }

    bool FlatVector::Equals(const FlatVector& other) const {
        return (X == other.x()) && (Y == other.y());
    }

}