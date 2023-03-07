#include <iostream>
#include "Sphere.h"
#include "Gizmos.h"
Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float angularVelocity, float mass, float radius, glm::vec4 colour) :
    Rigidbody::Rigidbody(SPHERE, position, velocity, 0, angularVelocity, mass)
{
    m_radius = radius;
    m_colour = colour;
    m_moment = 0.5f * mass * radius * radius;
    m_angularVelocity = angularVelocity;
}

Sphere::~Sphere()
{
    // If we had pointers we would delete (free memory) and assign to nullptr;
}

Sphere::Sphere()
{
    std::cout << "*** Default Constructor of Sphere ***"; // useful to have messages with default constructors which are only useful for the compiler
}

Sphere::Sphere(glm::vec2 position, float inclination, float speed, float angularVelocity, float mass, float radius, glm::vec4 colour) :
    Rigidbody::Rigidbody(SPHERE, position, inclination, speed, 0, angularVelocity, mass)
{
    m_radius = radius;
    m_colour = colour;
    m_moment = 0.5f * mass * radius * radius;
    m_angularVelocity = angularVelocity;
    //float speedx = speed * cos(glm::radians(inclination));
    //float speedy = speed * sin(glm::radians(inclination));
    //velocity = glm::vec2(speedx, speedy);
    //new Sphere(position, m_velocity, mass, m_radius, m_colour);
}

//void Sphere::draw()
//{
//    aie::Gizmos::add2DCircle(getPosition(), getRadius(), 32, getColour());
//}
//  following modification to be able to see your spheres rotating:
//void Sphere::draw()
//{
//    glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) *
//        m_radius;
//    aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
//    aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
//}
void Sphere::draw()
{
    glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) *
        m_radius;
    aie::Gizmos::add2DCircle(getPosition(), getRadius(), 32, getColour());
    aie::Gizmos::add2DLine(getPosition(), getPosition() + end, glm::vec4(1, 1, 1, 1));
}

// Gizmos::add2DCircle(const glm::vec2& center, float radius, unsigned int segments, const glm::vec4& colour, const glm::mat4* transform /*= nullptr*/)
// 
//    aie::Gizmos::add2DCircle(glm::vec2(0, 0), 1, 5, glm::vec4(1,2,3,4),transform);
//     aie::Gizmos::add2DCircle(getPosition(), getRadius(), 6, ,transform)
// 
// In the definition of the class, note how we have not added the fixedUpdate(), applyForce() or applyForceToActor() functions.
// These are implemented in the rigid body class, and as they will always be the same for all sub-classes, we won�t need to overload them here.
// However, because all our shape sub-classes require a different type of gizmo to represent them visually, it makes sense to provide them with unique draw() functions.
//
// The draw function will simply call the add2DCircle() function of the Gizmo class, passing in the appropriate arguments.This is a static function, and don�t forget that the Gizmo class
// is defined within the aie namespace.
//
// For now, you don�t need to derive classes for the plane or the boxes.All our experiments with Newton�s laws of motion and the projectile physics will be done with spheres.