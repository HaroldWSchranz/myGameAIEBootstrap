#pragma once
#include <glm/vec2.hpp>
#include <vector>
class PhysicsObject
{
protected:
    PhysicsObject() {}

public:
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;  // PhysicsObject is a pure abstract base class.
    virtual void draw() = 0;
    virtual void resetPosition() {};
};

