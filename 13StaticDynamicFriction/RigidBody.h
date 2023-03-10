#pragma once
#include <glm/vec2.hpp>
#include  <glm/ext.hpp>
#include <vector>
#include "PhysicsObject.h"
//#include "PhysicsScene.h"

static const float MIN_LINEAR_THRESHOLD =  0.0001f;  // should be static const?
static const float MIN_ANGULAR_THRESHOLD = 0.0001f; // should be static const?

class Rigidbody : public PhysicsObject {
public:
    Rigidbody(ShapeType shapeID, glm::vec2 position,
        glm::vec2 velocity, float orientation, float angularVelocity, float mass);

    Rigidbody(ShapeType shapeID, glm::vec2 position,
        float inclination, float speed, float orientation, float angularVelocity, float mass);

    Rigidbody();

    ~Rigidbody();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    //void applyForce(glm::vec2 force);
    void applyForce(glm::vec2 force, glm::vec2 pos);
    //void applyForceToActor(Rigidbody* actor2, glm::vec2 force);
    //(I’ve removed the applyForceToActor() function, since it’s a little redundant,
    //but feel free to append a glm::vec2 position argument if you wish to keep it.)
    //void applyForceToActor(Rigidbody* actor2, glm::vec2 force, glm::vec2 pos);
    //void resolveCollision(Rigidbody* actor2);

    void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

    glm::vec2 getPosition() const { return m_position; }
    float getOrientatation() { return m_orientation; }
    glm::vec2 getVelocity() { return m_velocity; }
    glm::vec2 setVelocity(glm::vec2 velocity) { return m_velocity = velocity; }

    float getAngularVelocity() { return m_angularVelocity; }

    float getElasticity() { return m_elasticity; }

    float getMass() { return m_mass; }

    float getMoment() { return m_moment; }

    // Add a function to Rigidbody to calculate the kinetic energy. For now this will just be linear kinetic energy,
    float getKineticEnergy();

    float getPotentialEnergy();

    float getEnergy();
    
protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    float m_elasticity = 1.0f;
    float m_mass;
    //float m_orientation;    //2D so we only need a single float to represent our orientation

    float m_orientation = 0.0f;   // Add the following variables to the Rigidbody class, and ensure they are initialized in the constructor(s).
    float m_angularVelocity = 0.0f;
    float m_moment = 0.0f;        // m_moment variable represents the moment of inertia, the rotational equivalent of mass
    float m_linearDrag = 0.05f;
    float m_angularDrag = 0.05f;
    //inline static constexpr float MIN_LINEAR_THRESHOLD =  0.0001f;  // should be static const?
    //inline static constexpr float MIN_ANGULAR_THRESHOLD = 0.0001f; // should be static const?
};

/*
MIN_LINEAR_THRESHOLD and MIN_ANGULAR_THRESHOLD can either be #define values, global
constant variables, or constant static member variables of the Rigidbody class.
*/