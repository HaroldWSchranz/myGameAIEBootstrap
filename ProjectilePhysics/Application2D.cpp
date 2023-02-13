#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
using namespace glm;

PhysicsApp::PhysicsApp() {
	// Why the underlines ... ??
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

	//m_physicsScene = new PhysicsScene();
	////m_physicsScene->setGravity(glm::vec2(0, 0));   // Newton's 1st Law:    zero gravity: setGravity(glm::vec2(0, 0));
	//m_physicsScene->setGravity(glm::vec2(0, -10)); // Newton's 2nd Law: nonzero gravity: setGravity(glm::vec2(0, -10));
	//m_physicsScene->setTimeStep(0.01f);

	// Call the setupContinuousDemo() function from your application’s startup() function,
	// and ensure you are drawing the gizmos during the draw() function.
	// void PhysicsApp::setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
	setupContinuousDemo(vec2(-40, 0), 45.0, 30.0, 10.0);
	//
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(vec2(0, -10));
	//m_physicsScene->setTimeStep(0.5f);
	m_physicsScene->setTimeStep(0.1f);

	float radius = 0.64f;
	float speed = 30;
	vec2 startPos(-40, 0);
	//float inclination = (float)M_PI / 4.0f; // 45 degrees
	//float inclination = 3.14159265358979f / 4.0f; // 45 degrees
	float inclination = 45.0f;
	//float speedx = speed * cos(radians(inclination));
	//float speedy = speed * sin(radians(inclination));
	//
	//m_physicsScene->addActor(new Sphere(
	//	startPos, vec2(speedx,speedy), 1, radius, vec4(1, 0, 0, 1)));
	//
	m_physicsScene->addActor(new Sphere(startPos, inclination, speed, 1, radius, vec4(1, 0, 0, 1)));
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

	//Ensure the Gizmos::clear() function is removed in the application’s update() function: 
	//aie::Gizmos::clear();

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
	//static float aspectRatio = 1.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();

}

void PhysicsApp::setupContinuousDemo(glm::vec2 startPos, float inclination,
	float speed, float gravity)
{
	float t = 0;
	float tStep = 0.1f;
	float radius = 0.32f;
	int segments = 16;
	glm::vec4 colour = glm::vec4(0, 1, 1, 1);

	while (t <= 8)
	{
		// calculate the x, y position of the projectile at time t 
		// x = x0 + v0x t
		// y = y0 + v0y - (1 / 2) g t ^ 2
		float speedx = speed * cos(radians(inclination));
		float x = startPos.x + speedx * t;
		float speedy = speed * sin(radians(inclination));
		float y = startPos.y + speedy * t - gravity * t * t / 2.0;

		aie::Gizmos::add2DCircle(vec2(x, y), radius, segments, colour);
		t += tStep;
	}
}
