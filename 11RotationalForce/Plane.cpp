#include "Plane.h"
#include "RigidBody.h"

#include <iostream>
using namespace glm;

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE)      // what are we suppose to do with this?
{
    m_distanceToOrigin = distance;
    m_normal = normal;
}

Plane::Plane() : PhysicsObject(ShapeType::PLANE) {
    m_distanceToOrigin = 0;
    m_normal = glm::vec2(0, 1);
}

Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep) //  Because all plane objects will be static,
{                                                          //   the fixedUpdate() function will be empty.
}

void Plane::draw()
{
    float lineSegmentLength = 300;
    glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
    // easy to rotate normal through 90 degrees around z
    glm::vec2 parallel(m_normal.y, -m_normal.x);
    glm::vec4 colourFade = m_colour;
    colourFade.a = 0;
    glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
    glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
    //aie::Gizmos::add2DLine(start, end, m_colour_line);
    aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, m_colour, colourFade);
    aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, m_colour, colourFade, colourFade);
    //aie::Gizmos::add2DLine(start, end, m_colour_line);
}

void Plane::resetPosition()  // What are we supposed to do with this???
{
}

//void Plane::resolveCollision(Rigidbody* actor2)
//{
//	glm::vec2 normal = m_normal; // assign the collision normal to the plane normal
//	glm::vec2 relativeVelocity = actor2->getVelocity();       // the relative velocity is the same as the rigidbody velocity,
//
//	float elasticity = 1; // a coefficient of elasticity(e) of 1 means that no energy will be lost during the collision.
//	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
//		((1 / actor2->getMass()));
//
//	glm::vec2 force = normal * j;
//
//	float kePre = actor2->getKineticEnergy();
//
//	//applyForceToActor(actor2, -force);
//	//applyForceToActor(actor2, +force);
//	actor2->applyForce(+force);           // My version has +force
//
//	float kePost = actor2->getKineticEnergy();
//
//	float deltaKE = kePost - kePre;
//	float devFrac = deltaKE / kePre;
//	std::cout << "KE: Before: " << kePre << "  After: " << kePost << "  Delta: " << deltaKE << " (" << devFrac << ")" << std::endl;
//	if (deltaKE > kePost * 0.01f)
//		std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";
//
//	std::cout << "Rigidbody::resolveCollision:" << std::endl;
//	std::cout << "normal = (" << normal.x << "," << normal.y << ")" << std::endl;
//	std::cout << "actor2->getVelocity() = (" << actor2->getVelocity().x << "," << actor2->getVelocity().y << ")" << std::endl;
//
//	std::cout << "relativeVelocity = (" << relativeVelocity.x << "," << relativeVelocity.y << ")" << std::endl;
//	std::cout << "impulse j = " << j << std::endl;
//}

//void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact)
//{
//	// the plane isn't moving, so the relative velocity is just actor2's velocity
//	glm::vec2 vRel = actor2->getVelocity();
//	float e = actor2->getElasticity();
//	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / actor2->getMass());
//	vec2 force = m_normal * j;
//	actor2->applyForce(force, contact - actor2->getPosition());
//}

void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact)
{
    // the position at which we'll apply the force relative to the object's COM 
    glm::vec2 localContact = contact - actor2->getPosition();

    // the plane isn't moving, so the relative velocity is just actor2's velocity at the contact point
        glm::vec2 vRel = actor2->getVelocity() + actor2->getAngularVelocity() * vec2(-localContact.y, localContact.x);
    float velocityIntoPlane = glm::dot(vRel, m_normal);

    // perfectly elasticity collisions for now 
    float e = 1;

    // this is the perpendicular distance we apply the force at relative to the COM, so Torque = F * r
        float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));

    // work out the "effective mass" - this is a combination of moment of 
    // inertia and mass, and tells us how much the contact point velocity  
    // will change with the force we're applying 
    float mass0 = 1.0f / (1.0f / actor2->getMass() + (r * r) / actor2 -> getMoment());

    float j = -(1 + e) * velocityIntoPlane * mass0;

    vec2 force = m_normal * j;

    float kePre = actor2->getKineticEnergy();

    actor2->applyForce(force, contact - actor2->getPosition());

    float kePost = actor2->getKineticEnergy();

    float deltaKE = kePost - kePre;
    if (deltaKE > kePost * 0.01f)
        std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";
}


// The other functions will simply set various member variables. You should be able to complete these by yourself.

/*
This should give you a complete resolveCollision() function for the plane. The last step is to call this
function from the sphere-to-plane collision detection functions.

One thing to note is that because the Plane class does not inherit from the Rigidbody class, we can’t
use virtual functions in this instance. We’ve simply made two functions in two classes that have the
same name.
If you expect this to get a little confusing as you add more shapes to your physics engine, you may
want to add the virtual function declaration to the PhysicsObject class.
*/