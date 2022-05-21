#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include<string>
#include<iostream>
using namespace std;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Texture* loadTexture(SDL_Renderer* renderer,const char* texture)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}
SDL_Texture* loadTexture2(SDL_Renderer* renderer,const char* texture)
{
	SDL_Surface* surface = SDL_LoadBMP(texture);
    Uint32 colorKey = SDL_MapRGB(surface->format, 255 , 255 , 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

	return tex;
}

void Draw(SDL_Renderer* renderer,SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	// copy a portion of the texture to the current rendering target.
	SDL_RenderCopy(renderer, tex, &src, &dest);
}