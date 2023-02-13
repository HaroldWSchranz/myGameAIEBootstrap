#include "Application2D.h"

// This should only appear in my repo
// https://vimeo.com/213005085/3609374652
// https://vimeo.com/213607377/77c8867175

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	//app->run("AIE", 1280, 720, false);
	app->run("AIE", 1920, 1080, false);

	// deallocation
	delete app;

	return 0;
}