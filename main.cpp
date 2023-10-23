#include <iostream>
#if WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Environment.h"
#include "Renderer.h"
#include <time.h>
#include "Timer.h"
#include "Food.h"
#include "Anthill.h"
#include "SillyAnt.h"
#include "AntBasePheromone.h"

static unsigned int windowWidth() { return 300; }
static unsigned int windowHeight() { return 300; }

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment * environment)
{
	std::cout << "Key pressed: " << key << std::endl;
	if(key == 'f'){
		int q = MathUtils::random(200,2000);
		std::cout << q << std::endl;
		Vector2<float> p = environment->randomPosition();
		new Food(environment, p, q);

	}
	else if(key == 'd'){
		std::vector<Food*> v = environment->getAllInstancesOf<Food>();
		if(v.size() != 0) {
			v[0]->setStatus(Agent::Status::destroy);
		}
	}
	else if(key == 'a'){
		Vector2<float> p = environment->randomPosition();
		Anthill * hill = new Anthill(environment, p);
		for (int i = 0; i < 10; ++i) {
			new AntBasePheromone(environment, hill, 100);
		}
	}
}

/// <summary>
/// Called at each time step.
/// </summary>
void onSimulate()
{
	Agent::simulate();
}

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/)
{
	// 1 - Initialization of SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS/* | SDL_INIT_AUDIO*/) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	// 2 - Initialization of the renderer
	Renderer::initialize(windowWidth(), windowHeight());

	// 3 - Creation of an environment
	Environment environment(windowWidth(), windowHeight());

	// 4 - We change the seed of the random number generator
	srand((unsigned int)time(NULL));

	// The main event loop...
	SDL_Event event;
	bool exit = false;
	while (!exit) 
	{
		// 1 - We handle events 
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'q'))
			{
				::std::cout << "Exit signal detected" << ::std::endl;
				exit = true;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				onKeyPressed((char)event.key.keysym.sym, &environment);
			}
		}
		// 2 - We update the simulation
		Timer::update(0.5);
		onSimulate();
		// 3 - We render the scene
		Renderer::getInstance()->flush();
	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();
	Agent::finalize();
	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
