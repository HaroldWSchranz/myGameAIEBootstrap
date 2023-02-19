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
	applyForce(gravity * m_mass * timeStep);
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

void Rigidbody::applyForce(glm::vec2 force)
{
	m_velocity += force / m_mass;
}

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
	actor2->applyForce(force);
	this->applyForce(-force);
}

void Rigidbody::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position); // calculate the collision normal of the plane along which the collision occurs.
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;       // the relative velocity between the two objects.

	float elasticity = 1; // a coefficient of elasticity(e) of 1 means that no energy will be lost during the collision.
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		((1 / m_mass) + (1 / actor2->getMass()));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, -force);
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
