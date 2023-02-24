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
    void applyForce(glm::vec2 force);
    void applyForceToActor(Rigidbody* actor2, glm::vec2 force);

    glm::vec2 getPosition() { return m_position; }
    float getOrientatation() { return m_orientation; }
    glm::vec2 getVelocity() { return m_velocity; }
    glm::vec2 setVelocity(glm::vec2 velocity) { return m_velocity = velocity; }
    float getMass() { return m_mass; }

    // Add a function to Rigidbody to calculate the kinetic energy. For now this will just be linear kinetic energy,
    float getKineticEnergy() { return 0.5*m_mass* glm::dot(m_velocity,m_velocity); }


    float getPotentialEnergy();

    void resolveCollision(Rigidbody* actor2);
    
protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    float m_mass;
    float m_orientation;    //2D so we only need a single float to represent our orientation
};

