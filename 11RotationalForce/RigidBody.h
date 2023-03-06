#pragma once
#include <glm/vec2.hpp>
#include  <glm/ext.hpp>
#include <vector>
#include "PhysicsObject.h"
//#include "PhysicsScene.h"

class Rigidbody : public PhysicsObject {
public:
    Rigidbody(ShapeType shapeID, glm::vec2 position,
        glm::vec2 velocity, float orientation, float mass);

    Rigidbody(ShapeType shapeID, glm::vec2 position,
        float inclination, float speed, float orientation, float mass);

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

    float getElasticity() { return elasticity; }

    float getMass() { return m_mass; }

    float getMoment() { return m_moment; }

    // Add a function to Rigidbody to calculate the kinetic energy. For now this will just be linear kinetic energy,
    float getKineticEnergy();

    float getPotentialEnergy();

    float getEnergy();
    
protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    float elasticity = 1.0f;
    float m_mass;
    //float m_orientation;    //2D so we only need a single float to represent our orientation

    float m_orientation;   // Add the following variables to the Rigidbody class, and ensure they are initialized in the constructor(s).
    float m_angularVelocity;
    float m_moment;        // m_moment variable represents the moment of inertia, the rotational equivalent of mass
};

