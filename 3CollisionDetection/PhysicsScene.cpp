#include "PhysicsScene.h"

//PhysicsScene::PhysicsScene()
//{
//	m_timeStep = 0.01f;
//	m_gravity = glm::vec2(0, 0);
//}

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
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

        // check for collisions (ideally you'd want to have some sort of 
        // scene management in place)
        int actorCount = m_actors.size();

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
            // reverse forces (= m_mass * m_velocity per timestep) to stop spheres dead
            sphere1->applyForce(-sphere1->getMass() * sphere1->getVelocity());
            sphere2->applyForce(-sphere2->getMass() * sphere2->getVelocity());
            return true;
        }
        return false;
    }
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




