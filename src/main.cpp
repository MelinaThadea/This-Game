#ifdef WIN32
#define SDL_MAIN_HANDLED 
#endif //WIN32

#include <iostream>
#include <cstdlib>
#include "Arena.h"
#include <SDL.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"
#include <ngl/NGLStream.h>



SDL_GLContext createOpenGLContext(SDL_Window * _window);
void setupShaders();

static int WIDTH = 640;
static int HEIGHT = 360;
static float ASPECT = static_cast<float>(WIDTH) / HEIGHT;



int main()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "error init sdl\n";
		return EXIT_FAILURE;
	}

	auto window = SDL_CreateWindow("Gather the Fruit Game",0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL ); //| SDL_WINDOW_RESIZABLE

	auto glContext = createOpenGLContext(window);
	if (!glContext)
	{
		std::cerr << "can't create GL context \n";
		exit(EXIT_FAILURE);
	}
	SDL_GL_MakeCurrent(window, glContext);
	ngl::NGLInit::instance();
	setupShaders();
	glClearColor(1, 1, 0,0); //BG COLOUR
	glEnable(GL_DEPTH_TEST);
	RenderGlobals::setView({ 0.0f, 20.0f,-17.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }); //CAM VIEW z is up
	RenderGlobals::setProjections(45.0f, ASPECT);


	//std::cout << "Simple Game\n"; //JUST FOR VISUALISATION
	//Arena arena(20, 20);
	Arena arena("maps/map1.png","maps/fruit1.png");
	//arena.setItem(4, 4, ItemType::Player);

	SDL_Event event;
	bool quit = false;
	int xDir = 0;
	int yDir = 0;

	

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type) // Keyboard Controls
			{
			case SDL_QUIT: quit = true; break; //look for the quit button on the window
			case SDL_KEYDOWN : //if button is pressed
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE: quit = true; break;
				case SDLK_LEFT: xDir = 1; break;
				case SDLK_RIGHT: xDir = -1; break;
				case SDLK_UP: yDir = 1; break;
				case SDLK_DOWN: yDir = -1; break;
				}
			break; //end key down

			case SDL_KEYUP: //if button is not pressed, everything stops
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT: xDir = 0; break; 
				case SDLK_RIGHT: xDir = 0; break;
				case SDLK_UP: yDir = 0; break;
				case SDLK_DOWN: yDir = 0; break;
				}
				break; //end key down


			}
		}// end poll event
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, WIDTH, HEIGHT);
		arena.keyEvent(xDir, yDir);
		arena.draw();

		//std::cout << RenderGlobals::getProjectMatrix() << '\n'; //JUST FOR VISUALISATION
		//std::cout << RenderGlobals::getViewMatrix() << '\n'; //JUST FOR VISUALISATION
		//std::cout << RenderGlobals::getVPMatrix() << '\n'; //JUST FOR VISUALISATION

		arena.update(0.5f);
		//auto shader = ngl::ShaderLib::instance();
		//shader->setUniform("MV", RenderGlobals::getViewMatrix());
		//shader->setUniform("MVP", RenderGlobals::getVPMatrix());

		//ngl::VAOPrimitives::instance()->draw("teapot"); //drawing teapot
		SDL_GL_SwapWindow(window);
		SDL_Delay(20);
	} // end game loop

	return EXIT_SUCCESS;
}


SDL_GLContext createOpenGLContext(SDL_Window* _window)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	return SDL_GL_CreateContext(_window);
}

//SET UP SHADERS!!
void setupShaders()
{
	auto shader = ngl::ShaderLib::instance();
	shader->use(ngl::nglDiffuseShader);
	shader->setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
	shader->setUniform("lightPos", 0.0f, 10.0f, 0.0f);
	shader->setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->setUniform("normalMatrix", ngl::Mat3());

	shader->use(ngl::nglCheckerShader);
	shader->setUniform("lightPos", 0.0f, 10.0f, 0.0f);
	shader->setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->setUniform("checkOn", true);
	shader->setUniform("colour1", 0.9f, 0.9f, 0.9f, 1.0f);
	shader->setUniform("colour2", 0.6f, 0.6f, 0.6f, 1.0f);
	shader->setUniform("checkSize", 10.0f);
	shader->setUniform("normalMatrix", ngl::Mat3());
	
}