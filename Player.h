#include "Object.h"


class Player
    {
    public:
        Player(SDL_Renderer* renderer,const char* textureSheet,int x, int y)
        {
        
            objTexture = loadTexture(renderer, textureSheet);
        
            xpos = x;
	        ypos = y;
            xspeed = 0;
            yspeed=0;
        }
            
        ~Player(){};

        void Render(SDL_Renderer* renderer){
            SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
            srcRect.x = 0;
            srcRect.y = 0;


            desRect.x = xpos;
            desRect.y = ypos;
            desRect.h = 40;
            desRect.w = 40;
            SDL_RenderCopy(renderer, objTexture, &srcRect, &desRect);
        }
        //SDL_Texture* loadTexture(const char* textureSheet, SDL_Renderer* ren);
        bool isInsideBox() {
            return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
        }
        void HandleMove(SDL_Event& e,int level){
            double  a;
            if(level==1) a=3;
            else{
                if(level==2) a=3.5;
                else a=4;
            }
            if(e.type==SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE: break;
                case SDLK_LEFT: xspeed=-a;yspeed=0; break;
                case SDLK_RIGHT: xspeed=a;yspeed=0;break;
                case SDLK_UP: xspeed=0;yspeed=-a; break;
                case SDLK_DOWN: xspeed=0;yspeed=a; break;
                default: break;
                }
            }
        }
        void Move(){
            xpos+=xspeed;
            ypos+=yspeed;
        }
        //version 1.0
        void moveRight(){
            xpos+=10;
        }
        void moveLeft(){
            xpos-=10;
        }
        void moveUp(){
            ypos-=10;
        }
        void moveDown(){
            ypos+=10;
        }
        bool collision(SDL_Texture* texture){
            
        }
        //version 1.0
        //void event(SDL_Window *window, SDL_Renderer* renderer){
            //SDL_Event e;
            //if(SDL_PollEvent(&e)==0) {};
            //if(e.type == SDL_QUIT) quitSDL(window, renderer);
            //if(e.type==SDL_KEYDOWN) {
                //switch (e.key.keysym.sym) {
                //case SDLK_ESCAPE: break;
                //case SDLK_LEFT: moveLeft(); break;
                //case SDLK_RIGHT: moveRight(); break;
                //case SDLK_UP: moveUp(); break;
                //case SDLK_DOWN: moveDown(); break;
                //default: break;
                //}
            //}
        //}
        int getxpos(){return xpos;}
        int getypos(){return ypos;}

        SDL_Rect getdesRect(){
            return desRect;
        }
    private:
        int xpos;
	    int ypos;
        int xspeed,yspeed;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, desRect;
        

};
