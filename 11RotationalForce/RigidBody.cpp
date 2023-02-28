#include "RigidBody.h"
#include "PhysicsScene.h"
#include <iostream>
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
// 
// CORRECT ORDER: update position then apply gravity
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	//applyForce(gravity * m_mass * timeStep);
	applyForce(gravity * m_mass * timeStep, m_position);
	m_orientation += m_angularVelocity * timeStep;
}
//
// REVERSED ORDER: applt gravity then update position
//void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
//{
//	applyForce(gravity * m_mass * timeStep);
//	m_position += m_velocity * timeStep;
//}

/*
Watch closely, and you’ll see the balls sink slowly into the plane.

A little though can explain why this happens.

The collision code between calls to fixedUpdate is zero-ing the ball’s velocities. If we apply gravity first, the ball’s velocity when it gets applied to its position is one frame’s worth of acceleration due to gravity. It doesn’t accumulate velocity like it does when free-falling, because its velocity gets zero’d again every frame, but it will move down a small amount each frame.

For this reason it’s best to apply gravity after updating the position – it prevents objects that rest on each other from “quicksanding”like this.

We’ll revisit these systematic errors and their other implications when we have a physically correct collision response working.
*/

/*
We need to pass a contact point into applyForce() to say where the force is applied, so that we can
calculate the torque applied to the rigidbody. Later we’ll update our collision detection algorithm so
that it identifies the contact point.
*/
void Rigidbody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	// use getMass() and getMoment() here in case we ever get it to do something more than just return mass...
	m_velocity += force / getMass();
	m_angularVelocity += (force.y * pos.x - force.x * pos.y) / getMoment();
}



/*
c.f. https://aie.instructure.com/courses/1024/pages/physics-for-games-collision-resolution
Tutorial - Collision Resolution - Introduction
https://aie.instructure.com/courses/1024/files/723947/download?wrap=1
The applyForceToActor() function applies the negative force to this actor, and the positive force to
actor2 (thus implementing the “equal and opposite” part of Newton’s third law).
*/
//void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force, glm::vec2 pos)
//{
//	actor2->applyForce(force, pos);
//	this->applyForce(-force, pos);
//}
//
//void Rigidbody::resolveCollision(Rigidbody* actor2)
//{
//	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position); // calculate the collision normal of the plane along which the collision occurs.
//	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;       // the relative velocity between the two objects.
//
//	float elasticity = 1; // a coefficient of elasticity(e) of 1 means that no energy will be lost during the collision.
//	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
//		((1 / m_mass) + (1 / actor2->getMass()));
//
//	glm::vec2 force = normal * j;
//
//	applyForceToActor(actor2, +force);
//
//	std::cout << "Rigidbody::resolveCollision:" << std::endl;
//	std::cout << "normal = (" << normal.x << "," << normal.y << ")" << std::endl;
//	std::cout << "actor2->getVelocity() = (" << actor2->getVelocity().x << "," << actor2->getVelocity().y << ")" << std::endl;
//	std::cout << "m_velocity = (" << m_velocity.x << "," << m_velocity.y << ")" << std::endl;
//	std::cout << "relativeVelocity = (" << relativeVelocity.x << "," << relativeVelocity.y << ")" << std::endl;
//	std::cout << "impulse j = " << j << std::endl;
//}

//void Rigidbody::resolveCollision(Rigidbody* actor2)
//{
//	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position); // calculate the collision normal of the plane along which the collision occurs.
//	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;       // the relative velocity between the two objects.
//
//	float elasticity = 1; // a coefficient of elasticity(e) of 1 means that no energy will be lost during the collision.
//	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
//		((1 / m_mass) + (1 / actor2->getMass()));
//
//	glm::vec2 force = normal * j;
//
//	float kePre = getKineticEnergy() + actor2->getKineticEnergy();
//
//	//applyForceToActor(actor2, -force);
//	applyForceToActor(actor2, +force);   // My version has +force
//
//	float kePost = getKineticEnergy() + actor2->getKineticEnergy();
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
//	std::cout << "m_velocity = (" << m_velocity.x << "," << m_velocity.y << ")" << std::endl;
//	std::cout << "relativeVelocity = (" << relativeVelocity.x << "," << relativeVelocity.y << ")" << std::endl;
//	std::cout << "impulse j = " << j << std::endl;
//}

void Rigidbody::resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{
	// find the vector between their centres, or use the provided direction
	// of force, and make sure it's normalised
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal :
		actor2->m_position - m_position);
	// get the vector perpendicular to the collision normal
	glm::vec2 perp(normal.y, -normal.x);
	// determine the total velocity of the contact points for the two objects,
	// for both linear and rotational
	// 'r' is the radius from axis to application of force
	float r1 = glm::dot(contact - m_position, -perp);
	float r2 = glm::dot(contact - actor2->m_position, perp);
	// velocity of the contact point on this object
	float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	// velocity of contact point on actor2
	float v2 = glm::dot(actor2->m_velocity, normal) +
		r2 * actor2->m_angularVelocity;
	if (v1 > v2) // they're moving closer
	{
		// calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to the force applied.
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);
		//float elasticity = 1;
		//glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 /
		//	(mass1 + mass2) * (v1 - v2) * normal;
		glm::vec2 force = (1.0f + getElasticity()) * mass1 * mass2 /
			(mass1 + mass2) * (v1 - v2) * normal;
		//apply equal and opposite forces
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);
	}
}



// DOES THIS BELONG IN Rigidbody.H OR Rigidbody.CPP (latter is better practice)
// We can then add a getPotentialEnergy() function to Rigidbody like so :
float Rigidbody::getPotentialEnergy()
{
	return -getMass() * glm::dot(PhysicsScene::getGravity(), getPosition());
}

float Rigidbody::getEnergy()
{
	return getKineticEnergy() + getPotentialEnergy();
}

/*
The line of code that calculates j (the impulse magnitude) is a bit long, but simply reflects the
formula presented earlier.

After calculating j, we multiply it by the collision normal (n). This gives us the force to apply to each
object. This is done by calling the applyForceToActor() function we’ve previously written. (If you
don’t have this function an explanation, if not the code, is given in the tutorial for Linear Force and
Momentum.)

The applyForceToActor() function applies the negative force to this actor, and the positive force to
actor2 (thus implementing the “equal and opposite” part of Newton’s third law).
We now have a collision resolution function that we can use to modify the velocities of the objects
involved in a collision.

In the next tutorial we’ll cover how we can integrate this function into our exiting collision detection
code, bringing the two systems together.

For now, explore the references and any web resources you find that explain similar approaches to
collision resolution. Are there any improvements you can make to the function we just wrote?

Next Tutorial:
Collision Resolution – Sphere to Sphere in Collision Response and Friction section
*/
