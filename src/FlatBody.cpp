#include "../include/FlatVector.h"
#include "../include/FlatBody.h"
#include "../include/FlatMath.h"
#include "FlatWorld.cpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

namespace FlatPhysics {

    FlatBody::FlatBody(const FlatVector& position, float mass, float restitution, float area, float density, bool isStatic, float r, float w, float h, ShapeType shape)
        : position_old(position), position_current(position), mass(mass), restitution(restitution), area(area), density(density), isStatic(isStatic),
            radius(r), width(w), height(h), shape(shape), angle(0), rotationalV(0), force(FlatVector(0,0)) {}

    std::optional<FlatBody> CreateCircleBody(const FlatVector &position, float mass, float restitution, bool isStatic, float r, std::string &errorMsg)
    {
        float area = r * r * M_PI;
        // if (area < FlatWorld::minSize){
        //     errorMsg = "Radius too small.";
        //     return std::nullopt;
        // }
        // if (area > FlatWorld::maxSize){
        //     errorMsg = "Radius too large.";
        //     return std::nullopt;
        // }

        float density = mass / area;
        // if (density > FlatWorld::maxDensity){
        //     errorMsg = "Circle too dense";
        //     return std::nullopt;
        // }
        // if (density < FlatWorld::minDensity){
        //     errorMsg = "Circle not dense enough";
        //     return std::nullopt;
        // }

        restitution = FlatMath::clamp(restitution, 0, 1);
        return FlatBody(position, mass, restitution, area, density, isStatic, r, 0, 0, ShapeType::Circle);
    }

    std::optional<FlatBody> CreateBoxBody(const FlatVector& position, float mass, float restitution, bool isStatic, float w, float h, std::string& errorMsg) {
        float area = w * h;
        if (area < FlatWorld::minSize) {
            errorMsg = "Dimensions too small.";
            return std::nullopt;
        }
        if (area > FlatWorld::maxSize) {
            errorMsg = "Dimensions too large.";
            return std::nullopt;
        }

    float density = mass / area;
    if (!isStatic){
        float density = mass / area;
        if (density > FlatWorld::maxDensity) {
            errorMsg = "Box too dense";
            return std::nullopt;
        }
        if (density < FlatWorld::minDensity) {
            errorMsg = "Box not dense enough";
            return std::nullopt;
        }
    }
        restitution = FlatMath::clamp(restitution, 0.0f, 1.0f);
        return FlatBody(position, mass, restitution, area, density, isStatic, 0, w, h, ShapeType::Box);
    }

    void FlatBody::step(float time, FlatVector gravity) {

        const FlatVector velocity = position_current - position_old;
        position_old = position_current;
        position_current = position_current + velocity + gravity * time * time;
        // std::cout << this->position_current.y() << "\n";

        this->force = FlatVector(0,0);
    }

    void FlatBody::addForce(FlatVector force){
        this->force+=force;
    }

    void FlatBody::move(FlatVector distance)
    {
        this->position_current += distance;
    }

    void FlatBody::moveTo(FlatVector position)
    {
        // std::cout << position.x() << " , " << position.y() << "\n";
        this->position_current = position;
    }

}
