#include "Application2D.h"

int main() {
	
	// allocation
	auto app = new PhysicsApp();

	// initialise and loop
	//app->run("AIE", 1280, 720, false);
	app->run("DIY Physics Engine: Sphere - Sphere", 1920, 1080, false);

	// deallocation
	delete app;

	return 0;
}