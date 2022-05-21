#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include<string>
#include<iostream>

using namespace std;
#define nullptr NULL
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
const string WINDOW_TITLE = "Treasure Hunt";

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event* g_event;
void logSDLError(std::ostream& os,const std::string &msg, bool fatal);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
