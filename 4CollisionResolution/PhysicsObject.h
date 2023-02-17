#pragma once
#include <glm/vec2.hpp>
#include <vector>

//enum ShapeType {
//    PLANE = 0,
//    SPHERE,
//    BOX
//};

enum ShapeType {
    PLANE = 0,
    SPHERE
};

class PhysicsObject
{
public:
    PhysicsObject();
    ~PhysicsObject();

protected:
    PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;  // PhysicsObject is a pure abstract base class.
    virtual void draw() = 0;
    virtual void resetPosition() {};

    ShapeType getShapeID() const {
        return m_shapeID;
    }

protected:
    ShapeType m_shapeID;
};
