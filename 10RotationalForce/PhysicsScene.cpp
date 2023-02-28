#include <iostream>
#include "PhysicsScene.h"
#include "PhysicsObject.h"

#include "Sphere.h"
#include "Plane.h"

//PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
//{
//}

glm::vec2 PhysicsScene::m_gravity{ 0,0 };

PhysicsScene::PhysicsScene() : m_timeStep(0.01f) {
    setGravity(glm::vec2(0, 0));
}

PhysicsScene::~PhysicsScene()
{
    for (auto pActor : m_actors)
    {
        delete pActor;
    }
}

// function pointer array for doing our collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
    PhysicsScene::plane2Plane,     PhysicsScene::plane2Sphere,
    PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
};
//static fn collisionFunctionArray[] =
//{
//   PhysicsScene::plane2Plane,  PhysicsScene::plane2Sphere,  PhysicsScene::plane2Box,
//   PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2Box,
//   PhysicsScene::box2Plane,    PhysicsScene::box2Sphere,    PhysicsScene::box2Box,
//};

void PhysicsScene::update(float dt)
{
    // update physics at a fixed time step
    static float accumulatedTime = 0.0f;
    accumulatedTime += dt;

    while (accumulatedTime >= m_timeStep) {
        for (auto pActor : m_actors) {
            pActor->fixedUpdate(m_gravity, m_timeStep);
        }
        accumulatedTime -= m_timeStep;

        // print out getTotalEnergy out every frame
        total_time += dt;
        std::cout << "total_time: " << total_time << " Total Energy : " << getTotalEnergy() << std::endl;

        // check for collisions (ideally you'd want to have some sort of 
        // scene management in place)
        int actorCount = static_cast<int>(m_actors.size()); // static cast to get rid of warning

        // need to check for collisions against all objects except this one.
        for (int outer = 0; outer < actorCount - 1; outer++)
        {
            for (int inner = outer + 1; inner < actorCount; inner++) // Note how the second for loop starts at outer+1 rather than 0.  We only want to compare each pair of objects
            {                                                        //  once rather than twice, and we don’t want to compare each object against itself
                PhysicsObject* object1 = m_actors[outer];
                PhysicsObject* object2 = m_actors[inner];

                int shapeId1 = object1->getShapeID();
                int shapeId2 = object2->getShapeID();

                // using function pointers
                int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
                fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
                if (collisionFunctionPtr != nullptr)
                {
                    // did a collision occur?
                    collisionFunctionPtr(object1, object2);
                }
            }
        }
    }
}

void PhysicsScene::updateGizmos()
{
}

void PhysicsScene::debugScene()
{
}

void PhysicsScene::draw()
{
    for (auto pActor : m_actors) {
        pActor->draw();
    }
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
    // try to cast objects to sphere and sphere
    Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
    Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
    // if we are successful then test for collision
    if (sphere1 != nullptr && sphere2 != nullptr)
    {
        // TODO do the necessary maths in here
        // TODO if the spheres touch, set their velocities to zero for now
        // You can calculate the distance between the two centres manually, or use the helper function glm::distance and pass the sphere centers in.
        // Compare this distance to the sum of the radii to determine whether a collision has taken place.
        if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) <= sphere1->getRadius() + sphere2->getRadius()) {
            // reverse forces (= m_mass * m_velocity per timestep) to stop spheres dead (MY WAY without setVelocity):
            //sphere1->applyForce(-sphere1->getMass() * sphere1->getVelocity());
            //sphere2->applyForce(-sphere2->getMass() * sphere2->getVelocity());
            // for now, just stop the spheres using setVelocity (which I had to invent in RigidBody.h):
            //sphere1->setVelocity(glm::vec2(0, 0));
            //sphere2->setVelocity(glm::vec2(0, 0));
            // Call void Rigidbody::resolveCollision(Rigidbody* actor2) on sphere1 with sphere2 as argument
            sphere1->resolveCollision(sphere2);
            return true;
        }
        return false;
    }
    return false;
}

float PhysicsScene::getTotalEnergy()
{
    float total = 0;
    for (auto it = m_actors.begin(); it != m_actors.end(); it++)
    {
        PhysicsObject* obj = *it;
        total += obj->getEnergy();
    }
    return total;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
    Sphere* sphere = dynamic_cast<Sphere*>(obj1);
    Plane* plane = dynamic_cast<Plane*>(obj2);
    //if we are successful then test for collision
    if (sphere != nullptr && plane != nullptr)
    {
        glm::vec2 collisionNormal = plane->getNormal();
        float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

        float intersection = sphere->getRadius() - sphereToPlane;
        float velocityOutOfPlane = glm::dot(sphere->getVelocity(), plane->getNormal());
        if (intersection > 0 && velocityOutOfPlane < 0)
        {
            //set sphere velocity to zero here
            //sphere->applyForce(-sphere->getVelocity() * sphere->getMass());
            plane->resolveCollision(sphere);

            return true;
        }
    }
    return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
    // reverse the order of arguments, as obj1 is the plane and obj2 is the sphere
    return sphere2Plane(obj2, obj1);
}


void PhysicsScene::checkForCollision()
{
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
    // We can just return false, as both planes are static and require no collision response
    return false;
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
    m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
    //https://en.cppreference.com/w/cpp/container/vector/erase
    //m_actors.erase(m_actors.i);
    //sceneActors.erase(std::find(sceneActors.begin(), sceneActors.end(), actor));
    // if condition for edge case:
    m_actors.erase(std::find(m_actors.begin(), m_actors.end(), actor));
}



/*
SHAPE_COUNT is a constant defined as the number of primitive shapes our physics engine handles 
(i.e., the number of enumerated values in the ShapeType enum).
If we make it the last item in the shapes enumerated type then it will always be set up correctly.

Be careful that SHAPE_COUNT is correct. If you have a 2x2 array of functions pointers, 
SHAPE_COUNT will need to be 2 for this to work. If you’ve already declared BOX in your ShapeType enum, 
it may be 3, which will cause a number of collisions to not work correctly. If this is the case, comment 
out the enum definition for BOX for now so that SHAPE_COUNT is 2.
*/

/*
Sphere-to-Sphere Collision:
In the Collision Detection tutorial we implemented the sphere2Sphere() function inside the
PhysicsScene class to detect collisions between two spheres.
Because we had yet to write the collision response function, when two spheres collided we simply
set the velocity of both spheres to (0,0).

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
 Sphere *sphere1 = dynamic_cast<Sphere*>(obj1);
 Sphere *sphere2 = dynamic_cast<Sphere*>(obj2);
 if (sphere1 != nullptr && sphere2 != nullptr) {
  vec2 dist = sphere1->getPosition() - sphere2->getPosition();
  if (glm::length(dist) < sphere1->getRadius() + sphere2->getRadius()){
   // collision
   // for now, just stop the spheres
   sphere1->setVelocity(vec2(0, 0));
   sphere2->setVelocity(vec2(0, 0));
   return true;
  }
 }
 return false;
}


*/