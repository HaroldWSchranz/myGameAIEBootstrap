#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <math.h>  
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	PhysicsScene* m_physicsScene;

	void setupContinuousDemo(glm::vec2 startPos, float inclination,
		float speed, float gravity);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	float m_timer;
};