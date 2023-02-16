#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);

	void removeActor(PhysicsObject* actor);

	void update(float dt);
	void updateGizmos();
	void debugScene();

	void draw();  // Is this necessary?

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;

	int SHAPE_COUNT = 2;		// is this right?
};

	// The sphere2Sphere function is a static function of PhysicsScene.
	// We’ll be adding more of these in later tutorials to cover the different code 
	// we need for checking collisions between different types of primitives.
