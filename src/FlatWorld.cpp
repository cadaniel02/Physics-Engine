#include "../include/FlatWorld.h"
#include <iostream>
#include <stdint.h>


namespace FlatPhysics
{

    float FlatWorld::minDensity = 0.5f;
    float FlatWorld::maxDensity = 22.0f;

    float FlatWorld::minSize = 0.01f * 0.01f;
    float FlatWorld::maxSize = 64.0f * 64.0f;

    FlatWorld::FlatWorld() : gravity(FlatVector(0, -9.81f)), bodyList(std::vector<FlatBody>()) {}

    void FlatWorld::step(float time)
    {
        const uint32_t substeps = 8;
        const float sub_dt = time / static_cast<float>(substeps);

        for (uint32_t i(substeps); i--;){
            for (int i = 0; i < bodyList.size(); ++i)
            {
                bodyList[i].step(sub_dt, this->gravity);
            }
            applyConstraint();
            solveCollisions();
        }
    }

    std::vector<FlatBody> FlatWorld::getBodies()
    {
        return bodyList;
    }

    void FlatWorld::addBody(FlatBody body)
    {
        this->bodyList.push_back(body);
    }

    void FlatWorld::setConstraint(FlatVector position, float radius)
    {
        // std::cout << "position: " << position.x() << " , " << position.y() << "radius: " << radius << "\n";
        constraint_center = position;
        constraint_radius = radius;
    }

    void FlatWorld::applyConstraint()
    {
        for (auto &body : bodyList)
        {
            const float dist = FlatMath::distance(constraint_center, body.GetPosition());

            if (dist > (constraint_radius - body.GetRadius()))
            {
                const FlatVector v = constraint_center - body.GetPosition();
                const FlatVector n = v / dist;
                const FlatVector new_position = constraint_center - n * (constraint_radius - body.GetRadius());

                body.moveTo(new_position);
                // body.addForce(n * body.GetRestitution());
            }
        }
    }

    void FlatWorld::solveCollisions() 
    {
        const uint32_t body_count = bodyList.size();
        for (int i = 0; i < body_count; ++i)
        {
            for (int j = i + 1; j < body_count; ++j){
                const FlatVector collision_axis = bodyList[i].GetPosition() - bodyList[j].GetPosition();
                const float dist = FlatMath::length(collision_axis);
                if (dist < bodyList[i].GetRadius() + bodyList[j].GetRadius()){
                    const FlatVector n = collision_axis / dist;
                    const float delta = bodyList[i].GetRadius() + bodyList[j].GetRadius() - dist;
                    bodyList[i].move(n * delta * 0.5f);
                    bodyList[j].move(-n * delta * 0.5f);
                }
            }
        }
    }
}