#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	SDL_Window* window;  // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2

	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                          // window title
	                          0,                                         // initial x position
	                          0,                                         // initial y position
	                          dm.w,                                      // width, in pixels
	                          dm.h,                                      // height, in pixels
	                          SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// The window is open: could enter program loop here (see SDL_PollEvent())
	// Setup renderer
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
	SDL_Rect r;
	r.x = 50;
	r.y = 50;
	r.w = dm.w - 100;
	r.h = dm.h - 100;

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(renderer, &r);

	SDL_Surface* sprite_s = SDL_LoadBMP("invader.bmp");
	const char* err = SDL_GetError();
	SDL_Texture* sprite = SDL_CreateTextureFromSurface(renderer, sprite_s);

	for (int n = 0; n < 360; n++) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, sprite, NULL, NULL);

		SDL_RenderPresent(renderer);
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
