#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "RigidBody.h"

class Box : public Rigidbody
{
public:
    Box();

    ~Box();

    Box(glm::vec2 position, glm::vec2 velocity, float orientation, float angularVelocity, float mass, float width, float height, glm::vec4 colour);

    Box(glm::vec2 position, float inclination, float speed, float orientation, float angularVelocity, float mass, float width, float height, glm::vec4 colour);

    bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

    void fixedUpdate(glm::vec2 gravity, float timeStep);

    void draw();

    glm::vec2 getExtents() const { return m_extents; }
    glm::vec2 getLocalX() { return m_localX; }
    glm::vec2 getLocalY() { return m_localY; }
    float getWidth()  { return 2 * m_extents.x; }
    float getHeight() { return 2 * m_extents.y; }

protected:
    float width;
    float height;

	glm::vec2 m_extents;   // the halfedge lengths  
	glm::vec4 m_colour;

	// store the local x,y axes of the box based on its angle of rotation 
	glm::vec2 m_localX;
	glm::vec2 m_localY;
};



/*

#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
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

*/