#include"Texture.h"


class Bomb{
    private:
        int xpos;
	    int ypos;
        SDL_Texture* objTexture;
        SDL_Rect srcRect, desRect;
    public:
        void create(SDL_Renderer* renderer,const char* textureSheet,int x, int y)
        {
        
            objTexture = loadTexture(renderer, textureSheet);
        
            xpos = x;
	        ypos = y;
        }
            
	
        void Render(SDL_Renderer* renderer){
            
            SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
            srcRect.x = 0;
            srcRect.y = 0;


            desRect.x = xpos;
            desRect.y = ypos;
            desRect.h = 30;
            desRect.w = 30;
            SDL_RenderCopy(renderer, objTexture, &srcRect, &desRect);
            
        }
        
        int getxpos(){return xpos;}
        int getypos(){return ypos;}
       
};
class Wall{
    private:
        int xpos;
	    int ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, desRect;
    public:
        void create(SDL_Renderer* renderer,const char* textureSheet,int x, int y)
        {
            
        
            objTexture = loadTexture(renderer, textureSheet);
        
            xpos = x;
	        ypos = y;
        }
            
	
        void RenderRow(SDL_Renderer* renderer){
            SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
            srcRect.x = 0;
            srcRect.y = 0;


            desRect.x = xpos;
            desRect.y = ypos;
            desRect.h = 20;
            desRect.w = 40;
            SDL_RenderCopy(renderer, objTexture, &srcRect, &desRect);
        }
        void RenderCol(SDL_Renderer* renderer){
            SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
            srcRect.x = 0;
            srcRect.y = 0;


            desRect.x = xpos;
            desRect.y = ypos;
            desRect.h = 40;
            desRect.w = 20;
            SDL_RenderCopy(renderer, objTexture, &srcRect, &desRect);
        }
        int getxpos(){return xpos;}
        int getypos(){return ypos;}
       
};
class Diamond{
    private:
        int xpos;
	    int ypos;
        int clear;
        SDL_Texture* objTexture;
        SDL_Rect srcRect, desRect;
    public:
        void create(SDL_Renderer* renderer,const char* textureSheet,int x, int y)
        {
        
            objTexture = loadTexture(renderer, textureSheet);
        
            xpos = x;
	        ypos = y;
            clear=0;
        }
            
	
        void Render(SDL_Renderer* renderer){
            if(clear!=1){
                SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
                srcRect.x = 0;
                srcRect.y = 0;


                desRect.x = xpos;
                desRect.y = ypos;
                desRect.h = 30;
                desRect.w = 30;
                SDL_RenderCopy(renderer, objTexture, &srcRect, &desRect);
            }
        }
        void Clear(){
            clear=1;
        }
        void xClear(){
            clear=0;
        }
        int getxpos(){return xpos;}
        int getypos(){return ypos;}
        int getclear(){return clear;}
       
};