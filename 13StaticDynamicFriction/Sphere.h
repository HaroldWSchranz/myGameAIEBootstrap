#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "RigidBody.h"

class Sphere : public Rigidbody
{
public:
    Sphere();

    ~Sphere();

    Sphere(glm::vec2 position, glm::vec2 velocity, float angularVelocity, float mass, float radius, glm::vec4 colour);

    Sphere(glm::vec2 position, float inclination, float speed, float angularVelocity, float mass, float radius, glm::vec4 colour);

    virtual void draw();

    float getRadius() { return m_radius; }
    glm::vec4 getColour() { return m_colour; }

protected:
    float m_radius;
    glm::vec4 m_colour;
};

