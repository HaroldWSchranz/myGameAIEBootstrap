#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	int xmin = 100;
	int xmax = 1920 - xmin;
	int dx = xmax - xmin;
	int ymin = 100;
	int ymax = 1080 - ymin;
	int dy = ymax - ymin;

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw a moving purple circle
	for (int i = 1; i<=32; i++) {
		m_2dRenderer->setRenderColour(0.25, 0.5, 1.0 - float(i)/32., 1);
		m_2dRenderer->drawCircle((cos(m_timer/float(i/8))) * (float)dx/(float(i)) + dx/2. + xmin, (sin(m_timer / float(i/6)) )* (float)dy / (float(i)) + dy/2. + ymin, float(i)*32/64.);

		m_2dRenderer->setRenderColour(0.9, float(i) / 32., float(i) / 64., 1);
		m_2dRenderer->drawCircle((cos(m_timer / float(i/4))) * (float)dx*2.25 / (float(i + 1)) + dx / 2 + xmin, (sin(m_timer / float(i/2))) * (float)dy * 2.25 / (float(i)) + dy / 2. + ymin, float(i) * 32 / 64.);

		m_2dRenderer->setRenderColour(0.9, 0.9, float(i) / 64., 1);
		m_2dRenderer->drawCircle((cos(m_timer / float(i / 2))) * (float)dx*2.5 / (float(i)) + dx / 2. + xmin, (sin(m_timer / float(i / 4))) * (float)dy * 2.5 / (float(i)) + dy / 2. + ymin, float(i) * 32 / 64.);
	
		m_2dRenderer->setRenderColour(0.9, 0.9, float(i+32) / 64., 1);
		m_2dRenderer->drawCircle((cos(m_timer / float(i / 4))) * (float)dx*2.75 / (float(i)) + dx / 2. + xmin, (sin(m_timer / float(i / 4))) * (float)dy*2.75 / (float(i)) + dy / 2. + ymin, float(i) * 32 / 64.);

		m_2dRenderer->setRenderColour(0.1, 0.2, 0.9, 1);
		m_2dRenderer->drawCircle((cos(m_timer / float(i / 2))) * (float)dx * 3.5 / (float(i)) + dx / 2. + xmin, (sin(m_timer / float(i / 2))) * (float)dy * 2.75 / (float(i)) + dy / 2. + ymin, float(i) * 32 / 64.);

	}

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->setRenderColour(1, 1, 1, 1);
	m_2dRenderer->drawText(m_font, fps, 0, ymax);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", xmax - 256, ymax);

	// done drawing sprites
	m_2dRenderer->end();
}