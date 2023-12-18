#include <SDL2/SDL.h>
#include <iostream>

SDL_Surface *load_image(char * buff,int size);

#define R_MASK 0xFF000000
#define R_SHIFT 24
#define G_MASK 0x00FF0000
#define B_SHIFT 16
#define B_MASK 0x0000FF00 
#define G_SHIFT 8
#define A_MASK 0x000000FF
#define A_SHIFT 0

#define BITS_PER_PIXEL 32

#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 480

int create_pixel(SDL_Surface* surface, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	int pixel = 0;
	pixel |= (r << surface->format->Rshift) & surface->format->Rmask;
	pixel |= (g << surface->format->Gshift) & surface->format->Gmask;
	pixel |= (b << surface->format->Bshift) & surface->format->Bmask;
	pixel |= (a << surface->format->Ashift) & surface->format->Amask;
	return pixel;
}

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }
	
	SDL_Surface *surface = SDL_CreateRGBSurface(0,SCREEN_WIDTH,SCREEN_HEIGHT,BITS_PER_PIXEL,R_MASK,G_MASK,B_MASK,A_MASK);
	if(!surface)
	{
		std::cout << "Failed to create surface\n";
		return -1;
	}

	SDL_LockSurface(window_surface);
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for(int j = 0; j < SCREEN_WIDTH; j++)
		{
			int pixel = create_pixel(window_surface, 255 * i, 255 * j, 255 * (255 - j),255);
			((int*)window_surface->pixels)[i*SCREEN_WIDTH+j] = pixel;
		}
	}
	SDL_UnlockSurface(window_surface);

	bool keep_window_open = true;
	while(keep_window_open)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e) > 0)
		{
			switch(e.type)
			{
				case SDL_QUIT:
					keep_window_open = false;
					break;
			}

			SDL_UpdateWindowSurface(window);
		}
	}
}

