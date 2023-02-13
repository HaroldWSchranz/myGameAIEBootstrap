#include "RigidBody.h"
// Start by implementing the constructors, which should initialize the member variables.
// The applyForce() function is where we apply Newton’s second law. 
// This function will modify the velocity of the object according to the object’s mass and how much force has been applied.
//
// Applying a force to an object will either speed it up or slow it down.That is to say, applying a force will change
// the acceleration of an object.By adding the acceleration to the current velocity, we find the object’s new velocity.
//
// As you would recall from the lecture, according to Newton’s Second Law acceleration is calculated by dividing force
// by mass(a = F / m).So, in the applyForce() function you will need to calculate accelerationand add it to the m_velocity
// member variable.You should be able to write this as one line of code.
//
// The applyForceToActor() function prototype is a variation of the applyForce() function.It allows us to simulate one
// actor “pushing” another.
// 
// You may recall Newton’s third law, which states “for every action, there is an equaland opposite reaction”.
// In the applyForceToActor() function you must first apply the input force to the input actor(by calling the applyForce()
// function of that actor), and then apply the opposite force to the current actor(by calling applyForce() on this using
// the negative force).
//
// Finally, the fixedUpdate() function will apply any forces to the actor(i.e., gravity) before calculating the final
// position.

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_orientation = orientation;
	m_mass = mass;
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, float inclination, float speed, float orientation, float mass)
{
	m_shapeID = shapeID;
	m_position = position;
	float speedx = speed * cos(glm::radians(inclination));
	float speedy = speed * sin(glm::radians(inclination));
	m_velocity = glm::vec2(speedx, speedy);
	m_orientation = orientation;
	m_mass = mass;
}


Rigidbody::Rigidbody()
{
}

Rigidbody::~Rigidbody()
{
}

// After applying gravity as a force, we add the updated vector to the actor’s position to get the new position of the actor.
// Why does it update position, then apply force (Integrator method?)
// Whether we apply the force of gravity before or after updating the position, we introduce a systematic error into our physics simulation. 
// For now its preferable to apply gravity afterwards. 
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	applyForce(gravity * m_mass * timeStep);
}

void Rigidbody::applyForce(glm::vec2 force)
{
	m_velocity += force / m_mass;
}

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
	actor2->applyForce(force);
	this->applyForce(-force);
}
