#ifndef FLATVECTOR_HPP
#define FLATVECTOR_HPP
namespace FlatPhysics{
    
    class FlatVector {
        private:
            float X;
            float Y;

        public:
            float x() const { return X; };
            float y() const { return Y; };

            // Constructor
            FlatVector(float x, float y);
            FlatVector();

            // Method to add another vector and return a new Vector2f
            FlatVector operator+(const FlatVector&) const;
            FlatVector& operator+=(const FlatVector&);
            FlatVector operator-(const FlatVector&) const;
            FlatVector& operator-=(const FlatVector&);
            FlatVector operator-() const;

            // Method to multiply by a scalar and return a new Vector2f
            FlatVector operator*(float scalar) const;
            FlatVector operator/(float scaler) const;

            bool Equals(const FlatVector& other) const;
    };
}

#endif