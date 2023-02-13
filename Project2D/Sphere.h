#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>  
#include "RigidBody.h"
#include "Gizmos.h"

class Sphere : public Rigidbody
{
public:
    Sphere(glm::vec2 position, glm::vec2 velocity,
        float mass, float radius, glm::vec4 colour);
    ~Sphere();

    Sphere();

    Sphere(glm::vec2 position, float inclination, float speed,
        float mass, float radius, glm::vec4 colour);

    virtual void draw();

    float getRadius() { return m_radius; }
    glm::vec4 getColour() { return m_colour; }

protected:
    float m_radius;
    glm::vec4 m_colour;
};

