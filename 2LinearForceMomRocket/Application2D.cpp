#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
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
	//
	//m_physicsScene->setGravity(glm::vec2(0, 0));   // Newton's 1st Law:    zero gravity: setGravity(glm::vec2(0, 0));
	//m_physicsScene->setGravity(glm::vec2(0, -10)); // Newton's 2nd Law: nonzero gravity: setGravity(glm::vec2(0, -10));
	//m_physicsScene->setTimeStep(0.01f);

	//Sphere* ball;
	//ball = new Sphere(glm::vec2(-80, 0), glm::vec2(10, 30), 3.0f, 4, glm::vec4(1, 0, 0, 1));
	//m_physicsScene->addActor(ball);
	////
	//// Zero gravity
	//m_physicsScene->setGravity(vec2(0, 0));  // turn off gravity
	//
	//Sphere* ball1 = new Sphere(vec2(-4, 0), vec2(0, 0), 4.0f, 4, vec4(1, 0, 0, 1));
	//Sphere* ball2 = new Sphere(vec2(4, 0), vec2(0, 0), 4.0f, 4, vec4(0, 1, 0, 1));
	//
	//m_physicsScene->addActor(ball1);
	//m_physicsScene->addActor(ball2);
	//
	//ball1->applyForceToActor(ball2, vec2(10, 0));
	////
	//// turn off gravity
	//m_physicsScene->setGravity(vec2(0, 0));
	//
	//Sphere* ball1B = new Sphere(vec2(-50, 10), vec2(0), 4.0f, 4, vec4(1, 0, 0, 1));
	//Sphere* ball2B = new Sphere(vec2(+50, 10), vec2(0), 4.0f, 4, vec4(0, 1, 0, 1));
	//
	//m_physicsScene->addActor(ball1B);
	//m_physicsScene->addActor(ball2B);
	//
	//ball1B->applyForce(vec2(30, 0));
	//ball2B->applyForce(vec2(-15, 0));
	//
	// simulate a simple rocket motor
	// Finally, you can simulate a simple rocket motor.
	// Create a sphere in the centre of the screen, this is the rocket. Set gravity to zero.
	m_physicsScene->setGravity(glm::vec2(0, 0));   // zero gravity
	m_physicsScene->setTimeStep(0.01f);            // timestep
	float rocketMass = 4.0f;
	Sphere* ballRocket = new Sphere(vec2(0, 0), vec2(0, 1), rocketMass, 4, vec4(0, 1, 0, 1));
	m_physicsScene->addActor(ballRocket);
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

	// how to access ballRocket? Need to create ballExhaust
	// In the update function, at time intervals, you need to:
	// 1. Reduce the mass of the rocket by M to simulate fuel being used
	// 2. Create a new sphere of mass M next to the rocket to simulate an exhaust gas particle(ensuring that the two spheres won�t collide � in fact, this simulation will work better if you turn off collision detection altogether)
	// 3. Use applyForceToActor() to apply force to the exhaust gas from the rocket(make sure it is in the correct direction)
	// 4. Repeat until all the mass has been used up

	float exhaustMass = 0.04f;
	while (rocketMass >= exhaustMass) {
		rocketMass -= exhaustMass;
		Sphere* ballExhaust = new Sphere(vec2(0, -5), vec2(0, -10), exhaustMass, 1, vec4(0, 1, 1, 1));
		m_physicsScene->addActor(ballExhaust);
	}

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
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();

}