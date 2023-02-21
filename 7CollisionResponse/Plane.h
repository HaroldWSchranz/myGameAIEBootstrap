#pragma once
#include  <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include "RigidBody.h"
#include "PhysicsObject.h"
#include "Gizmos.h"

class Plane : public PhysicsObject
{
public:
    Plane(glm::vec2 normal, float distance);       // what happens to this in cpp file???
    Plane();                                       // Do we need this default constructor?
    ~Plane();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);  //  Because all plane objects will be static, the fixedUpdate() function will be empty.
    virtual void draw();
    virtual void resetPosition();

    glm::vec2 getNormal() { return m_normal; }
    float getDistance() { return m_distanceToOrigin; }

    glm::vec4 m_colour_line = glm::vec4(0, 0, 1, 1);
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);

    glm::vec2 m_normal;
    float m_distanceToOrigin;

    void resolveCollision(Rigidbody* actor2); // 20280222: Is this forward declaration OK?

protected:
   // glm::vec2 m_normal;
   // float m_distanceToOrigin;
};

