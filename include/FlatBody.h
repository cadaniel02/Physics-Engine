#ifndef FLATBODY_H
#define FLATBODY_H

#include "FlatVector.h"
#include <string>
#include <optional>

namespace FlatPhysics
{

    enum ShapeType {
        Circle = 0,
        Box = 1
    };

    class FlatBody
    {
    private:
        FlatBody(const FlatVector &position, float mass, float restitution, float area, float density, bool isStatic, float r, float w, float h, ShapeType shape);

        FlatVector position_current;
        FlatVector position_old;
        FlatVector force;
        float angle;
        float rotationalV;

        float mass;
        float restitution;
        float area;
        float density;

        bool isStatic;

        float radius;
        float width;
        float height;

        ShapeType shape;

    public:

        void step(float time, FlatVector gravity);

        void move(FlatVector distance);

        void moveTo(FlatVector position);

        void addForce(FlatVector force);

        // Getters

        FlatVector GetPosition() const{ return position_current; }
        float GetMass() const { return mass; }
        float GetRestitution() const { return restitution; }
        float GetArea() const { return area; }
        float GetDensity() const { return density; }

        bool GetIsStatic() const { return isStatic; }

        float GetRadius() const { return radius; }
        float GetWidth() const { return width; }
        float GetHeight() const { return height; }

        ShapeType GetShape() const { return shape; }

        friend std::optional<FlatBody> CreateCircleBody(const FlatVector &position, float mass, float restitution, bool isStatic, float r, std::string &errorMsg);
        friend std::optional<FlatBody> CreateBoxBody(const FlatVector &position, float mass, float restitution, bool isStatic, float w, float h, std::string &errorMsg);
    };

    std::optional<FlatBody> CreateCircleBody(const FlatVector &position, float mass, float restitution, bool isStatic, float r, std::string &errorMsg);
    std::optional<FlatBody> CreateBoxBody(const FlatVector &position, float mass, float restitution, bool isStatic, float w, float h, std::string &errorMsg);

}

#endif