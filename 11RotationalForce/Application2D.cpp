#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "Plane.h"
#include "Sphere.h"
using namespace glm;

PhysicsApp::PhysicsApp() {

}

PhysicsApp::~PhysicsApp() {

}

bool PhysicsApp::startup() {

	//	m_2dRenderer = new aie::Renderer2D();
	//
	//	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	//	m_shipTexture = new aie::Texture("./textures/ship.png");
	//
	//	m_font = new aie::Font("./font/consolas.ttf", 32);
	//	
	//	m_timer = 0;
	//
	//	return true;
		// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	////m_physicsScene->setGravity(glm::vec2(0, 0)); // zero gravity: setGravity(glm::vec2(0, 0));
	//m_physicsScene->setGravity(glm::vec2(0, -10)); //  nonzero gravity: setGravity(glm::vec2(0, -10));
	//m_physicsScene->setTimeStep(0.01f);
	//
	//Sphere* ball;
	//ball = new Sphere(glm::vec2(0, 30), glm::vec2(0, 0), 3.0f, 4, glm::vec4(1, 0, 0, 1));
	//m_physicsScene->addActor(ball);
	//
	//Plane* plane;
	//plane = new Plane(glm::vec2(0, 1), -30);
	//m_physicsScene->addActor(plane);

	//  DROPPING BALLS ON A PLANE:
	//m_physicsScene->setGravity(vec2(0, -9.82f));
	//m_physicsScene->setTimeStep(0.01f);
	//
	//Sphere* ball1 = new Sphere(vec2(-40, 20), vec2(0,0), 4.0f, 4, vec4(0.25, 0.25, 0.25, 1));
	//Sphere* ball2 = new Sphere(vec2(-10, 30), vec2(0,0), 4.0f, 4, vec4(1, 1, 1, 1));
	//Sphere* ball3 = new Sphere(vec2( 10, 40), vec2(0,0), 4.0f, 4, vec4(1, 1, 0, 1));
	//Sphere* ball4 = new Sphere(vec2( 40, 50), vec2(0,0), 4.0f, 4, vec4(1, 0, 1, 1));
	//
	//Sphere* ball5 = new Sphere(vec2(-40,  5), vec2(0, 30), 4.0f, 4, vec4(1, 0, 0, 1));
	//Sphere* ball6 = new Sphere(vec2(-10, 15), vec2(0, 25), 4.0f, 4, vec4(0, 1, 1, 1));
	//Sphere* ball7 = new Sphere(vec2( 10, 25), vec2(0, 20), 4.0f, 4, vec4(0, 1, 0, 1));
	//Sphere* ball8 = new Sphere(vec2( 40, 35), vec2(0, 15), 4.0f, 4, vec4(0, 0, 1, 1));
	//
	//Plane* plane = new Plane(vec2(0, 1), -30);
	//
	//m_physicsScene->addActor(ball1);
	//m_physicsScene->addActor(ball2);
	//m_physicsScene->addActor(ball3);
	//m_physicsScene->addActor(ball4);
	//m_physicsScene->addActor(ball5);
	//m_physicsScene->addActor(ball6);
	//m_physicsScene->addActor(ball7);
	//m_physicsScene->addActor(ball8);
	//m_physicsScene->addActor(plane);

	// Billiard Ball Simulation: 
	// The lecture slides for this session discuss the following situation using billiard balls :
	// • The cue ball’s(A) speed is 11.11 m / s(40 km / hr), going east, ball 2 (B)is stationary
	// • The cue ball weighs 170g, numbered balls 160g
	// • The coefficient of elasticity is 1
	// • The collision normal is(-1, 0)
	//		o The cue ball’s velocity points directly towards the numbered ball’s centre, so the normal will point directly back
	//
	// Create a simulation that reproduces this problem.
	// 
	// Run your simulationand use breakpoints to check if the velocities of your spheres after the collision
	// match the expected velocities in the worked problem in the lecture slides.If you’ve used a different
	// velocityand mass for either of your spheres, work through the math yourself to double check the
	// results of your simulation.
	// 
	// In both of the example problems presented in the lecture slides, the collision normal has been
	// calculated for you.You will find that the collision normal calculated by your collision resolution
	// function will match the values listed in the slides.
	// EXAMPLE 1
	//m_physicsScene->setGravity(vec2(0, 0));
	//m_physicsScene->setTimeStep(0.01f);
	//
	//Sphere* ball1 = new Sphere(vec2( 0, 0), vec2(11.11,0), 170.f, 4, vec4(0.25, 0.25, 0.25, 1));
	//Sphere* ball2 = new Sphere(vec2(20, 0), vec2(0,0),     160.f, 4, vec4(1, 1, 1, 1));
	//
	//m_physicsScene->addActor(ball1);
	//m_physicsScene->addActor(ball2);
	// SWAP BALLS TO SEE SYMMETRY
	//m_physicsScene->setGravity(vec2(0, 0));
	//m_physicsScene->setTimeStep(0.01f);
	//
	//Sphere* ball1 = new Sphere(vec2(20, 0), vec2(    0, 0), 160.f, 4, vec4(0.25, 0.25, 0.25, 1));
	//Sphere* ball2 = new Sphere(vec2( 0, 0), vec2(11.11, 0), 170.f, 4, vec4(1, 1, 1, 1));
	//
	//m_physicsScene->addActor(ball1);
	//m_physicsScene->addActor(ball2);
	// EXAMPLE 2
	//m_physicsScene->setGravity(vec2(0, 0));
	//m_physicsScene->setTimeStep(0.01f);
	
	//Sphere::Sphere(glm::vec2 position, float inclination, float speed, float mass, float radius, glm::vec4 colour) :
	//	Rigidbody(SPHERE, position, inclination, speed, 0, mass)
	// COLLINEAR:
	//Sphere* ball1 = new Sphere(vec2(0, 0), 0, 11.1, 170.f, 4, vec4(1, 1, 1, 1));
	//Sphere* ball2 = new Sphere(vec2(8.01, 0), vec2(0, 0), 160.f, 4, vec4(0.25, 0.25, 0.25, 1));
	// ANGLE 10 WITH ball2 on x axis:
	//Sphere* ball1 = new Sphere(vec2(0, 0), 10, 11.1, 170.f, 4, vec4(1, 1, 1, 1));
	//Sphere* ball2 = new Sphere(vec2(8.01, 0), vec2(0, 0), 160.f, 4, vec4(0.25, 0.25, 0.25, 1));
	// ANGLE 10 WITH ball2 on collision normal (0.7501, 0.6613):
	//Sphere* ball1 = new Sphere(vec2(0, 0), 10, 11.1, 170.f, 4, vec4(1, 1, 1, 1));
	//float eps = 0.000095;
	//float eps = 0.00009;
	//Sphere* ball2 = new Sphere(vec2(6.0008+eps, 5.2904+eps), vec2(0, 0), 160.f, 4, vec4(0.25, 0.25, 0.25, 1));
	////Sphere* ball2 = new Sphere(vec2(6.001, 5.291), vec2(0, 0), 160.f, 4, vec4(0.25, 0.25, 0.25, 1));
	//m_physicsScene->addActor(ball1);
	//m_physicsScene->addActor(ball2);

	//
// Tests to perform with your Physics Engine
// (THIS MIGHT DEPEND ON: Tutorial – Collision Response: Sphere to Sphere)
//Once you have sphere to sphere collisions and sphere to plane collisions,
//you should try the following situations to verify your code:
//
//Newton’s Cradle
//
//Place two vertical planes as walls, and line up 5 perfectly elastic spheres touching each other.
//Give the first one a velocity along the x-axis. You should observe Newton’s Cradle behaviour,
//with the balls on the left and right carrying all the momentum as they bounce back and forth into each other.

//m_physicsScene->setGravity(vec2(0, 0));
//m_physicsScene->setTimeStep(0.001f);
//
//Sphere* ball0 = new Sphere(vec2(-70, 0), vec2(0, 0), 32.0f, 8, vec4(1, 1, 1, 1));
//
//Sphere* ball1 = new Sphere(vec2(-50, 0), vec2(32, 0), 4.0f, 4, vec4(1, 0, 0, 1));
//Sphere* ball2 = new Sphere(vec2(-10, 0), vec2(0, 0), 4.0f, 4, vec4(0, 1, 0, 1));
//Sphere* ball3 = new Sphere(vec2(0, 0), vec2(0, 0), 4.0f, 4, vec4(0, 0, 1, 1));
//Sphere* ball4 = new Sphere(vec2(10, 0), vec2(0, 0), 4.0f, 4, vec4(1, 1, 0, 1));
//Sphere* ball5 = new Sphere(vec2(20, 0), vec2(0, 0), 4.0f, 4, vec4(1, 0, 1, 1));
//
//Sphere* ball6 = new Sphere(vec2(+70, 0), vec2(0, 0), 32.0f, 8, vec4(1, 1, 1, 1));
//
//Plane* plane1 = new Plane(vec2(-1, 0), -90);
//Plane* plane2 = new Plane(vec2(+1, 0), -90);
//
//m_physicsScene->addActor(ball0);
//
//m_physicsScene->addActor(ball1);
//m_physicsScene->addActor(ball2);
//m_physicsScene->addActor(ball3);
//m_physicsScene->addActor(ball4);
//m_physicsScene->addActor(ball5);
//
//m_physicsScene->addActor(ball6);
//
//m_physicsScene->addActor(plane1);
//m_physicsScene->addActor(plane2);


/*
Asymmetrical Newton’s Cradle

Make one of the balls heavier (and maybe a different colour?) than the others. See what happens,
and justify the behaviour to yourself in physical terms.
*/
//m_physicsScene->setGravity(vec2(0, 0));
//m_physicsScene->setTimeStep(0.001f);
//
//Sphere* ball0 = new Sphere(vec2(-70, 0), vec2(0, 0), 400.0f, 8, vec4(1, 1, 1, 1));
//
//Sphere* ball1 = new Sphere(vec2(-50, 0), vec2(32, 0), 4.0f, 4, vec4(1, 0, 0, 1));
//Sphere* ball2 = new Sphere(vec2(-10, 0), vec2(0, 0), 4.0f, 4, vec4(0, 1, 0, 1));
//Sphere* ball3 = new Sphere(vec2(0, 0), vec2(0, 0), 4000.0f, 6, vec4(0, 0, 1, 1));
//Sphere* ball4 = new Sphere(vec2(10, 0), vec2(0, 0), 4.0f, 4, vec4(1, 1, 0, 1));
//Sphere* ball5 = new Sphere(vec2(20, 0), vec2(0, 0), 4.0f, 4, vec4(1, 0, 1, 1));
//
//Sphere* ball6 = new Sphere(vec2(+70, 0), vec2(0, 0), 400.0f, 8, vec4(1, 1, 1, 1));
//
//Plane* plane1 = new Plane(vec2(-1, 0), -90);
//Plane* plane2 = new Plane(vec2(+1, 0), -90);
//
//m_physicsScene->addActor(ball0);
//
//m_physicsScene->addActor(ball1);
//m_physicsScene->addActor(ball2);
//m_physicsScene->addActor(ball3);
//m_physicsScene->addActor(ball4);
//m_physicsScene->addActor(ball5);
//
//m_physicsScene->addActor(ball6);
//
//m_physicsScene->addActor(plane1);
//m_physicsScene->addActor(plane2);

//
//m_physicsScene->setGravity(vec2(0, 0));
//m_physicsScene->setTimeStep(0.01f);
//Plane* plane1 = new Plane(vec2(-1, 0), -96);
//Plane* plane2 = new Plane(vec2(+1, 0), -96);
//Plane* plane3 = new Plane(vec2(0, +1), -52);
//Plane* plane4 = new Plane(vec2(0, -1), -52);
//
//Sphere* ball1 = new Sphere(vec2(+16, +16), vec2(-16, +16), 4.0f, 4, vec4(1, 1, 0, 1));
//Sphere* ball2 = new Sphere(vec2(+16, -16), vec2(+16, -16), 4.0f, 4, vec4(0, 1, 1, 1));
//Sphere* ball3 = new Sphere(vec2(-16, +16), vec2(-16, +16), 4.0f, 4, vec4(0, 1, 0, 1));
//Sphere* ball4 = new Sphere(vec2(-16, -16), vec2(+16, -16), 4.0f, 4, vec4(0, 0, 1, 1));
//Sphere* ball5 = new Sphere(vec2(0, 0),     vec2(0, 0),     4.0f, 4, vec4(1, 0, 1, 1));
//
//m_physicsScene->addActor(plane1);
//m_physicsScene->addActor(plane2);
//m_physicsScene->addActor(plane3);
//m_physicsScene->addActor(plane4);
//
//m_physicsScene->addActor(ball1);
//m_physicsScene->addActor(ball2);
//m_physicsScene->addActor(ball3);
//m_physicsScene->addActor(ball4);
//m_physicsScene->addActor(ball5);
//
//m_physicsScene->setGravity(vec2(0, 0));
//m_physicsScene->setTimeStep(0.01f);
//Plane* plane1 = new Plane(vec2(-1, 0), -96);
//Plane* plane2 = new Plane(vec2(+1, 0), -96);
//Plane* plane3 = new Plane(vec2(0, +1), -52);
//Plane* plane4 = new Plane(vec2(0, -1), -52);
//
//Sphere* ball01 = new Sphere(vec2(+16, +16), vec2(-16,-16), 4.0f, 4, vec4(1, 1, 0, 1));
//Sphere* ball02 = new Sphere(vec2(+16, -16), vec2(+16,-16), 4.0f, 4, vec4(1, 1, 0, 1));
//Sphere* ball03 = new Sphere(vec2(-16, +16), vec2(-16,+16), 4.0f, 4, vec4(1, 1, 0, 1));
//Sphere* ball04 = new Sphere(vec2(-16, -16), vec2(+16,+16), 4.0f, 4, vec4(1, 1, 0, 1));
//
//Sphere* ball05 = new Sphere(vec2(+32, +32), vec2(-16,-16), 4.0f, 4, vec4(1, 0, 0, 1));
//Sphere* ball06 = new Sphere(vec2(+32, -32), vec2(+16,-16), 4.0f, 4, vec4(1, 0, 0, 1));
//Sphere* ball07 = new Sphere(vec2(-32, +32), vec2(-16,+16), 4.0f, 4, vec4(1, 0, 0, 1));
//Sphere* ball08 = new Sphere(vec2(-32, -32), vec2(+16,+16), 4.0f, 4, vec4(1, 0, 0, 1));
//
//Sphere* ball09 = new Sphere(vec2(+24, +24), vec2(-16, -16), 4.0f, 4, vec4(0, 0, 1, 1));
//Sphere* ball10 = new Sphere(vec2(+24, -24), vec2(+16, -16), 4.0f, 4, vec4(0, 0, 1, 1));
//Sphere* ball11 = new Sphere(vec2(-24, +24), vec2(-16, +16), 4.0f, 4, vec4(0, 0, 1, 1));
//Sphere* ball12 = new Sphere(vec2(-24, -24), vec2(+16, +16), 4.0f, 4, vec4(0, 0, 1, 1));
//
//Sphere* ball13 = new Sphere(vec2(+ 8, + 8), vec2(-16,-16), 4.0f, 4, vec4(1, 0, 1, 1));
//Sphere* ball14 = new Sphere(vec2(+ 8, - 8), vec2(+16,-16), 4.0f, 4, vec4(1, 0, 1, 1));
//Sphere* ball15 = new Sphere(vec2(- 8, + 8), vec2(-16,+16), 4.0f, 4, vec4(1, 0, 1, 1));
//Sphere* ball16 = new Sphere(vec2(- 8, - 8), vec2(+16,+16), 4.0f, 4, vec4(1, 0, 1, 1));
//
//m_physicsScene->addActor(plane1);
//m_physicsScene->addActor(plane2);
//m_physicsScene->addActor(plane3);
//m_physicsScene->addActor(plane4);
//
//m_physicsScene->addActor(ball01);
//m_physicsScene->addActor(ball02);
//m_physicsScene->addActor(ball03);
//m_physicsScene->addActor(ball04);
//m_physicsScene->addActor(ball05);
//m_physicsScene->addActor(ball06);
//m_physicsScene->addActor(ball07);
//m_physicsScene->addActor(ball08);
//m_physicsScene->addActor(ball09);
//m_physicsScene->addActor(ball10);
//m_physicsScene->addActor(ball11);
//m_physicsScene->addActor(ball12);
//m_physicsScene->addActor(ball13);
//m_physicsScene->addActor(ball14);
//m_physicsScene->addActor(ball15);
//m_physicsScene->addActor(ball16);
//
//	//  DROPPING BALL ON A PLANE:
//	m_physicsScene->setGravity(vec2(0, -9.82f));
//	m_physicsScene->setTimeStep(0.01f);
//	
//	Sphere* ball1 = new Sphere(vec2(0, 50), vec2(0,0), 4.0f, 4, vec4(0.0, 0.0, 0.75, 1));
//
//	Plane* plane = new Plane(vec2(0, 1), -30);
//	
//	m_physicsScene->addActor(ball1);
//
//	m_physicsScene->addActor(plane);
//
	//  DROPPING BALLS ON A PLANE:
m_physicsScene->setGravity(vec2(0, -9.82f));
m_physicsScene->setTimeStep(0.01f);

Sphere* ball1 = new Sphere(vec2(0, 40), vec2(0.0f, -10.0f), 8.0f, 8, vec4(0.5, 0.0, 1.0, 1));
Sphere* ball2 = new Sphere(vec2(0, 20), vec2(0, 0),         8.0f, 8, vec4(0.5, 0.5, 1.0, 1));
Sphere* ball3 = new Sphere(vec2(0, 0), vec2(0.0f, 10.0f),   8.0f, 8, vec4(0.0, 0.0, 1.0, 1));

Plane* plane = new Plane(vec2(0, 1), -30);
Plane* plane1 = new Plane(vec2(-1, 0), -96);
Plane* plane2 = new Plane(vec2(+1, 0), -96);

m_physicsScene->addActor(ball1);
m_physicsScene->addActor(ball2);
m_physicsScene->addActor(ball3);

m_physicsScene->addActor(plane);
m_physicsScene->addActor(plane1);
m_physicsScene->addActor(plane2);
//

return true;
}

void PhysicsApp::shutdown() {

	//delete m_font;
	// delete m_texture;
	//delete m_shipTexture;
	//delete m_2dRenderer;
}

void PhysicsApp::update(float deltaTime) {

	//	m_timer += deltaTime;
	//
	//	// input example
	//	aie::Input* input = aie::Input::getInstance();
	//
	//	// Update the camera position using the arrow keys
	//	float camPosX;
	//	float camPosY;
	//	m_2dRenderer->getCameraPos(camPosX, camPosY);
	//
	//	if (input->isKeyDown(aie::INPUT_KEY_UP))
	//		camPosY += 500.0f * deltaTime;
	//
	//	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	//		camPosY -= 500.0f * deltaTime;
	//
	//	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//		camPosX -= 500.0f * deltaTime;
	//
	//	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	//		camPosX += 500.0f * deltaTime;
	//
	//	m_2dRenderer->setCameraPos(camPosX, camPosY);
	//
	//	// exit the application
	//	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	//		quit();
	// 
		// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw() {

	//	// wipe the screen to the background colour
	//	clearScreen();
	//
	//	// begin drawing sprites
	//	m_2dRenderer->begin();
	//
	//	// demonstrate animation
	//	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);
	//
	//	// demonstrate spinning sprite
	//	m_2dRenderer->setUVRect(0,0,1,1);
	//	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);
	//
	//	// draw a thin line
	//	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);
	//
	//	// draw a moving purple circle
	//	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);
	//
	//	// draw a rotating red box
	//	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);
	//
	//	// draw a slightly rotated sprite with no texture, coloured yellow
	//	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	//	
	//	// output some text, uses the last used colour
	//	char fps[32];
	//	sprintf_s(fps, 32, "FPS: %i", getFPS());
	//	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	//	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);
	//
	//	// done drawing sprites
	//	m_2dRenderer->end();
	//
		// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 4, 16);
	// done drawing sprites
	m_2dRenderer->end();

}



/*
When we collide a Sphere with a Plane, r will always be zero, and no torque will be induced. If we
drop a Box on to a plane so that it hits with two contact points, then the average contact point is the
centre of the colliding face, and no torque is induced.
If we drop a box that starts off at an angle (not 45 degrees on a square!), so that it collides with a
horizontal plane by one point, then torque will be induced.
Test that the following Rigidbody to Plane collisions do the following:
• A sphere does not gain any angular velocity when dropped on a plane.
• A box aligned with world axes (m_orientation =0) dropped on to a horizontal plane does not
gain any angular velocity.
• A box dropped at an angle does gain angular velocity. The more it spins after each bounce,
the lower its bounce will be. If it hits the plane with a large value of r, then a smaller force
will be applied due to the lower “effective mass”, giving rise to less linear acceleration. This
also makes sense in terms of energy, because the total kinetic energy is being divided
between linear kinetic energy and rotational kinetic energy. The split is different with each
bounce.
• The energy diagnostics do not show a significant change in the total energy in the system
when the off-centre box hits the plane.


TODO:
It may be useful at this point to start adding various “scene” functions to your Application class,
rather than changing out the code in startup(). Give them descriptive names like bouncyBall(),
boxTest() and so on to make it easier to keep testing your physics engine as you add more features.
*/