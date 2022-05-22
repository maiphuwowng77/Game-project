#include<vector>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<SDL2/SDL_ttf.h>
#include<sstream>

#include "Player.h"

using namespace std;
#define nullptr NULL
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
const string WINDOW_TITLE = "Treasure Hunt";
void logSDLError(std::ostream& os,const std::string &msg, bool fatal);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void setBackGround(SDL_Renderer *renderer);
void win(SDL_Renderer* renderer,int score);
void lose(SDL_Renderer* renderer,int score);
void treasure(SDL_Renderer* renderer);
bool Treasure(Player player);
void createBomb(SDL_Renderer* renderer,const char* bombimage,int n);
void renderBomb(SDL_Renderer* renderer,int n);
void createDiamond(SDL_Renderer* renderer,const char* diamondimage);
void renderDiamond(SDL_Renderer* renderer);
bool RandDiamond(Player player);
bool explode(Player player,int n);
int DIAMOND(Player player,int level);
void createWall(SDL_Renderer*renderer,int level);
void renderWall(SDL_Renderer*renderer,int level);
bool collision(Player player,int level);
void RenderScore(SDL_Renderer* renderer, int score);
void createrandDiamond(SDL_Renderer* renderer, int level);
bool valid(int p, int q, int level);
void Score(SDL_Renderer* renderer, int score);

int Menu(SDL_Renderer* renderer,SDL_Event e);
Bomb bomb[40];
Bomb bombZ[10];
Wall wall[150];
Diamond diamond[12];
Diamond randDiamond;
int main(int argc, char* argv[])
{
	srand(time(0));
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event mainEvent;
	SDL_Event e;
	int score = 0;
	//bool isRunning = true;

	int n;// so qua bom
	int level ;// do kho
	initSDL(window,renderer);
	//renderMenu(renderer);
	// Hien Menu va lua chon level
	level=Menu(renderer,e);
	if(level==1) n=20;
	else {
		if(level==2) n=0;
		else {
			if(level==3) n=10;
			else quitSDL(window,renderer);
		}

 	}
	// khoi tao nhan vat tai vi tri (0,0)
	Player player(renderer,"image/Mario.bmp",0,0);
	// tao vị tri dat bom theo level
	createBomb(renderer,"image/bomb.bmp",n);
	// xay tuong theo level
	createWall(renderer,level);
	// tao ra vị tri kim cuong co dinh neu level khac 1
	if(level!=1) createDiamond(renderer,"image/diamond.bmp");
	bool player_alive=true;
	// tao vị trí kim cuong bat ki
	randDiamond.Clear();
	createrandDiamond(renderer,level);
	//main loop
	while (player_alive)
	{
		// tai hinh nen
		setBackGround(renderer);
		// tai hinh bom
		renderBomb(renderer,n);
		// tai hinh tuong
		renderWall(renderer,level);
		// cap nhat diem so
		RenderScore(renderer,score);
		// tạo kim cuong tại vị tri bat ky khi nguoi choi da lay duoc vien kim cuong cu
		if(randDiamond.getclear()==1) {
			createrandDiamond(renderer,level);
		}
		// tai hinh anh kim cuong random
		randDiamond.Render(renderer);
		// tai hinh anh kim cuong co dinh khi level khac 1
		if(level!=1)renderDiamond(renderer);
		// tai hinh anh nhan vat
		player.Render(renderer);
		// tai hinh anh kho bau
		treasure(renderer);
		//draw to the screen
        SDL_RenderPresent(renderer);
		// lay su kien ban phim
		while (SDL_PollEvent(&mainEvent))
        {
            if (mainEvent.type == SDL_QUIT)
            {
                quitSDL(window,renderer);
				break;
            }
			if(mainEvent.type==SDL_KEYDOWN) {
				// lay su kien ban phim di chuyen nhan vat
				player.HandleMove(mainEvent,level);
				
            }
            
        }
		// di chuyen nhan vat
		player.Move();
		//player.event(window,renderer);
		// Kiem tra nguoi choi co di ra khoi man hinh ko?
		if(player.isInsideBox()==false){player_alive=false;break;}
		else{
			// Kiem tra nguoi choi co dam vao tuong ko?
			if(collision(player,level)==true){
				player_alive=false;
				score -=300;
				// hien hinh anh vu va cham
				SDL_Rect desRect = player.getdesRect();
				desRect.x -=100;
				desRect.y -=100;
				if(desRect.x<-20) desRect.x=-20;
				if(desRect.y<-20) desRect.y=-20;
				desRect.w = 250;
				desRect.h = 250;
				SDL_Texture*explodeTexture=loadTexture2(renderer, "image/collision.bmp");
				SDL_RenderCopy(renderer,explodeTexture,NULL,&desRect);
				SDL_RenderPresent(renderer);
				SDL_Delay(2500);
				break;
			}
			else{
				// Kiem tra nguoi choi co dam phai bom ko
				if(explode(player,n)==true) {
					player_alive=false;
					score -=500;
					// hien hinh anh vu no
					SDL_Rect desRect = player.getdesRect();
					desRect.x -=100;
					desRect.y -=100;
					if(desRect.x<-20) desRect.x=-20;
					if(desRect.y<-20) desRect.y=-20;
					desRect.w = 250;
					desRect.h = 250;
					SDL_Texture*explodeTexture=loadTexture2(renderer, "image/explosion.bmp");
					SDL_RenderCopy(renderer,explodeTexture,NULL,&desRect);
					SDL_RenderPresent(renderer);
					SDL_Delay(2500);
					break;
				}
				else {
					// Kiem tra nguoi choi co lay duoc kim cuong co dinh ko?
					if(DIAMOND(player,level)!=-1){
						score+=100;
						diamond[DIAMOND(player,level)].Clear();
					}
					else{
						// Kiem tra nguoi choi co lay duoc kim cuong random ko?
						if(RandDiamond(player)==true){
							score+=50;
							randDiamond.Clear();
						}
						else {
							// Kiem tra nguoi choi da lay duoc kho bau chua
							if(Treasure(player)==true) {
								score+=1000;
								// hien hinh anh kho báu
								SDL_SetRenderDrawColor(renderer, 0,0,0, 100);
								// clear the window to background color
								SDL_RenderClear(renderer);
								SDL_Texture*treasureTexture=loadTexture2(renderer, "image/treasure2.bmp");
								SDL_RenderCopy(renderer,treasureTexture,NULL,NULL);
								SDL_RenderPresent(renderer);
								SDL_Delay(2500);
								break;
							}
						}
					}
				}
			}
		}
		
	}
	if(player_alive==true) win(renderer,score);// hinh anh win và diem so dat duoc
	else lose(renderer,score); // hinh anh game over

	quitSDL(window,renderer);
	return 0;
}


void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
{
 os << msg << " Error: " << SDL_GetError() << std::endl;
 if (fatal) {
 SDL_Quit();
 exit(1);
 }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	logSDLError(std::cout, "SDL_Init", true);
	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
	//Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
	SDL_RENDERER_PRESENTVSYNC);
	//Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
	//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
	if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
	if ( SDL_WaitEvent(&e) != 0 &&(e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
	return;
	SDL_Delay(100);
	}
}
// Tao Menu
int Menu(SDL_Renderer* renderer,SDL_Event e){
	//SDL_Texture*menuTexture = loadTexture(renderer, "image/Menu.bmp");
	//SDL_RenderCopy(renderer,menuTexture,NULL,NULL);

	//SDL_RenderPresent(renderer);
	//SDL_Event e;
	//bool a = true;
	while(true){
		SDL_Texture*menuTexture = loadTexture(renderer, "image/Menu.bmp");
		SDL_RenderCopy(renderer,menuTexture,NULL,NULL);

		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP: return 1;
					case SDLK_ESCAPE: return 0;
					case SDLK_LEFT: return 2;
					case SDLK_RIGHT: return 3;
					default: break;
				}
				return 0;
			}
			//SDL_Delay(100);
		}
	}
    
}
// load hinh nen
void setBackGround(SDL_Renderer *renderer) {
	//set background color.
	//SDL_Texture*menuTexture = loadTexture(renderer, "BG.bmp");
	//SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
	//SDL_SetRenderDrawColor(renderer, 100,180,11, 100);
    SDL_SetRenderDrawColor(renderer, 96,173, 13, 100);
	// clear the window to background color
    SDL_RenderClear(renderer);
}
// load hinh anh win và diem so
void win(SDL_Renderer* renderer,int score){
	//SDL_SetRenderDrawColor(renderer, 0,0,0, 100);
	// clear the window to background color
	SDL_RenderClear(renderer);
	SDL_Texture*winTexture=loadTexture(renderer, "image/win.bmp");
	SDL_RenderCopy(renderer,winTexture,NULL,NULL);
	//TTF_Font* font=NULL;
	//SDL_Rect desRect;
	//SDL_Surface* surface = NULL;
    //SDL_Texture* texture = NULL;
	//SDL_Color fg = { 243, 156, 18 };
	//stringstream ss;
	//ss<<score;
	//string text="Your score: "+ ss.str();
	//font = TTF_OpenFont("VeraMoBd.ttf", 30);
	//surface =  TTF_RenderText_Solid(font,text.c_str(), fg);
	//surface = TTF_RenderText_Solid(font,text.c_str(),fg);
    //texture = SDL_CreateTextureFromSurface(renderer, surface);
    //SDL_FreeSurface(surface);
	//desRect.x = 360; desRect.y = 50;
    //desRect.w = 200; desRect.h = 50;
    //SDL_RenderCopy(renderer, texture, NULL, &desRect);
    //SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);
	SDL_Delay(1500);
	Score(renderer,score);
    waitUntilKeyPressed();
}
// load hinh anh game over
void lose(SDL_Renderer* renderer,int score){
	SDL_Texture*loseTexture=loadTexture(renderer, "image/gameover.bmp");
	SDL_RenderCopy(renderer,loseTexture,NULL,NULL);
	SDL_RenderPresent(renderer);
	if(score>0){
		SDL_Delay(2000);
		Score(renderer,score);
	}
	
    waitUntilKeyPressed();
}
//hien hinh anh kho bau
void treasure(SDL_Renderer* renderer){
	SDL_Rect desRect, srcRect;
	SDL_Texture*treasureTexture=loadTexture(renderer, "image/treasure.bmp");
	SDL_QueryTexture(treasureTexture, NULL, NULL, &srcRect.w, &srcRect.h);
	srcRect.x = 0;
    srcRect.y = 0;

    desRect.x = 740;
    desRect.y = 540;
    desRect.h = 60;
    desRect.w = 60;
	SDL_RenderCopy(renderer,treasureTexture,&srcRect,&desRect);
	SDL_RenderPresent(renderer);
}
// Kiem tra xem nguoi choi da den cho kho bau chua?
bool Treasure(Player player){
	int m=player.getxpos()-740;
	int n=player.getypos()-540;
	if(m*m+n*n<40*40){return true;}// Canh cua texture la 20
	else return false;
}


// Tao ra 10 vi tri dat bom bat ki
void createBomb(SDL_Renderer* renderer,const char* bombimage,int n){
	if(n==10){
		bombZ[0].create(renderer,bombimage,200,30);
		bombZ[1].create(renderer,bombimage,30,390);
		bombZ[2].create(renderer,bombimage,230,440);
		bombZ[3].create(renderer,bombimage,240,240);
		bombZ[4].create(renderer,bombimage,400,180);
		bombZ[5].create(renderer,bombimage,380,330);
		bombZ[6].create(renderer,bombimage,400,450);
		bombZ[7].create(renderer,bombimage,480,550);
		bombZ[8].create(renderer,bombimage,560,100);
		bombZ[9].create(renderer,bombimage,660,20);
	}
	else{
		int a = (SCREEN_WIDTH-80)/30;
		int b = (SCREEN_HEIGHT-80)/30;
		for(int i= 0;i<n;i++){
			int x = (rand()%a +2)*30;
			int y = (rand()%b +2)*30;
			bomb[i].create(renderer,bombimage,x,y);
			
		}
	}
}
//Hien bom len man hinh theo level
void renderBomb(SDL_Renderer* renderer,int n){
	if(n==10){
		for(int i=0;i<n;i++){
			bombZ[i].Render(renderer);
		}
	}
	else {
		for(int i=0;i<n;i++){
			bomb[i].Render(renderer);
		}
	}
	
}
// Kiem tra xem nguoi choi co di vao bom khong?
bool explode(Player player,int n){
	bool a= false;
	if(n==10){
		for(int i=0;i<n;i++){
			int m=player.getxpos()-bombZ[i].getxpos()+5;
			int n=player.getypos()-bombZ[i].getypos()+5;
			if(m*m+n*n<30*30){a = true;break;}// Canh cua texture la 30
		}
	}
	else{
		for(int i=0;i<n;i++){
			int m=player.getxpos()-bomb[i].getxpos()+5;// khoang cach giua 2 tam của 2 hình
			int n=player.getypos()-bomb[i].getypos()+5;
			if(m*m+n*n<30*30){a = true;break;}// Canh cua texture la 30
		}
	}
	return a;
}
// cap nhat diem so
void RenderScore(SDL_Renderer* renderer, int score){
	TTF_Font* font=NULL;
	SDL_Rect desRect;
	SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
	SDL_Color fg = { 243, 156, 18 };
	stringstream ss;
	ss<<score;
	string text="Your score: "+ ss.str();
	//font = TTF_OpenFont("lazy.ttf", 30);
	//surface =  TTF_RenderText_Solid(font,text.c_str(), fg);
	//surface = TTF_RenderText_Solid(font,text.c_str(),fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
	desRect.x = 700; desRect.y = 0;
    desRect.w = 80; desRect.h = 20;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);
    SDL_DestroyTexture(texture);
}
// tao ra me cung ( xay tuong )
void createWall(SDL_Renderer*renderer,int level){
	if(level!=1){
		//y tu 40 den 580
		for(int i=0;i<14;i++){
			wall[i].create(renderer,"image/wallcol.bmp",0,(i+1)*40);
		}
		for(int i=14;i<27;i++){
			wall[i].create(renderer,"image/wallcol.bmp",780,(i-14)*40);
		}
		for(int i=28;i<=31;i++){
			wall[i].create(renderer,"image/wallcol.bmp",200,160+(i-28)*40);
		}
		for(int i=32;i<=38;i++){
			wall[i].create(renderer,"image/wallcol.bmp",440,20+(i-32)*40);
		}
		for(int i=39;i<=41;i++){
			wall[i].create(renderer,"image/wallcol.bmp",520,(i-31)*40);
		}
		for(int i=42;i<=43;i++){
			wall[i].create(renderer,"image/wallcol.bmp",520,(i-29)*40);
		}
		for(int i=44;i<=48;i++){
			wall[i].create(renderer,"image/wallcol.bmp",640,20+(i-44)*40);
		}
		for(int i=49;i<=52;i++){
			wall[i].create(renderer,"image/wallcol.bmp",640,420+(i-49)*40);
		}
		for(int i=53;i<=54;i++){
			wall[i].create(renderer,"image/wallcol.bmp",320,420+(i-53)*40);
		}
		for(int i=55;i<=71;i++){
			wall[i].create(renderer,"image/wallrow.bmp",(i-52)*40,0);
		}
		for(int i=72;i<=89;i++){
			wall[i].create(renderer,"image/wallrow.bmp",(i-72)*40,580);
		}
		for(int i=90;i<=91;i++){
			wall[i].create(renderer,"image/wallrow.bmp",20+(i-90)*40,320);
		}
		for(int i=92;i<=94;i++){
			wall[i].create(renderer,"image/wallrow.bmp",200+(i-92)*40,160);
		}
		for(int i=95;i<=102;i++){
			wall[i].create(renderer,"image/wallrow.bmp",200+(i-95)*40,300);
		}
		wall[103].create(renderer,"image/wallrow.bmp",500,300);
		for(int i=104;i<=108;i++){
			wall[i].create(renderer,"image/wallrow.bmp",340+(i-104)*40,420);
		}
		for(int i=109;i<=111;i++){
			wall[i].create(renderer,"image/wallrow.bmp",200+(i-109)*40,500);
		}
		wall[112].create(renderer,"image/wallrow.bmp",300,500);
		for(int i=113;i<=114;i++){
			wall[i].create(renderer,"image/wallrow.bmp",700+(i-113)*40,300);
		}
	}
}
// hien hinh anh me cung
void renderWall(SDL_Renderer* renderer,int level){
	if(level!=1){
		for(int i=0;i<=54;i++){
			wall[i].RenderCol(renderer);
		}
		for(int i=55;i<=114;i++){
			wall[i].RenderRow(renderer);
		}
	}
}
// Kiem tra xem nguoi choi co dam vao tuong ko?
bool collision(Player player,int level){
	if(level==1) return false;
	int m=player.getxpos();
	int n=player.getypos();
	if(m<20&&n>40&&n<600) return true;
	if(n>560&&m>=0&&m<720) return true;
	if(m>760&&n>=0&&n<520) return true;
	if(n<20&&m>100&&m<800) return true;
	if(m>=20&&m<100&&n>300&&n<340) return true;
	if(n>140&&n<180&&m>180&&m<320) return true;
	if(m>180&&m<220&&n>140&&n<320) return true;
	if(m>180&&m<540&&n>280&&n<320) return true;
	if(m>500&&m<540&&n>280&&n<440) return true;
	if(m>300&&m<540&&n>400&&n<440) return true;
	if(m>300&&m<340&&n>400&&n<520) return true;
	if(m>180&&m<340&&n>480&&n<520) return true;
	if(m>420&&m<460&&n>=20&&n<=300) return true;
	if(m>500&&m<540&&n>500&&n<600) return true;
	if(m>620&&m<660&&n>=20&&n<220) return true;
	if(m>620&&m<660&&n>400&&n<600) return true;
	if(m>680&&m<800&&n>280&&n<320) return true;
	return false;
}
// tao ra vị tri kim cuong co dinh
void createDiamond(SDL_Renderer* renderer,const char* diamondImage){
	diamond[0].create(renderer,diamondImage,350,30);
	diamond[1].create(renderer,diamondImage,30,350);
	diamond[2].create(renderer,diamondImage,240,190);
	diamond[3].create(renderer,diamondImage,290,440);
	diamond[4].create(renderer,diamondImage,470,330);
	diamond[5].create(renderer,diamondImage,350,450);
	diamond[6].create(renderer,diamondImage,530,30);
	diamond[7].create(renderer,diamondImage,740,30);
	diamond[8].create(renderer,diamondImage,570,540);
	diamond[9].create(renderer,diamondImage,750,330);
	diamond[10].create(renderer,diamondImage,400,270);
}
// load hinh anh kim cuong co dinh
void renderDiamond(SDL_Renderer* renderer){
	for(int i=0;i<11;i++){
		diamond[i].Render(renderer);
	}
}
// Kiem tra xem nguoi choi co lay duoc kim cuong ko? Neu lay duoc thi là vien so may
int DIAMOND(Player player,int level){
	if(level==1) return -1;
	int a=-1;
	for(int i=0;i<11;i++){
		if(diamond[i].getclear()==1) continue;
		int m=player.getxpos()-diamond[i].getxpos()+5;
		int n=player.getypos()-diamond[i].getypos()+5;
		if(m*m+n*n<30*30){a = i;break;}// Canh cua texture la 30
	}
	return a;
}
// tao vien kim cuong random
void createrandDiamond(SDL_Renderer* renderer,int level){
	int a = (SCREEN_WIDTH-80)/30;
	int b = (SCREEN_HEIGHT-80)/30;
	//if(randDiamond.getclear()==1){
	int x,y;
	randDiamond.xClear();
	do{
		x = (rand()%a +1)*30;
		y = (rand()%b +1)*30;
	} while(valid(x,y,level)==false);
	
	randDiamond.create(renderer,"image/diamond.bmp",x,y);
		//randDiamond.Render(renderer);
	//}
}
// Kiem tra vi tri dat kim cuong co trung voi vị tri dat bom ko?
bool valid(int m, int n, int level){
	bool a = true;
	int p = m/30;
	int q = n/30;
	if(level==3){
		if((p==7&&q==1)||(p==1&&q==13)||(p==8&&q==15)||(p==8&&q==8)||(p==13&&q==6)||(p==13&&q==11)||(p==13&&q==15)||(p==16&&q==18)||(p==19&&q==3)||(p==22&&q==1)){
			a = false;
		}
	}
	else{
		if(level==1){
			for(int i=0;i< 20;i++){
				int x = bomb[i].getxpos()/30;
				int y = bomb[i].getypos()/30;
				if(p == x && q == y){
					a= false;
					break;
				}
			}
		}
	}
	return a;
}
// Kiem tra xem nguoi choi có lay duoc vien kim cuong random ko?
bool RandDiamond(Player player){
	int m=player.getxpos()-randDiamond.getxpos()+5;
	int n=player.getypos()-randDiamond.getypos()+5;
	if(m*m+n*n<30*30){return true;}
	return false;
}
// hien diem so nguoi choi dat duoc
void Score(SDL_Renderer* renderer, int score){
	
	SDL_SetRenderDrawColor(renderer, 0,0, 0, 100);
	// clear the window to background color
    SDL_RenderClear(renderer);
	SDL_Texture* scoreTexture;
	SDL_Rect desRect, srcRect;
	
	srcRect.x = 0;
    srcRect.y = 0;

    desRect.x = 0;
    desRect.y = 50;
    desRect.h = 500;
    desRect.w = 800;
	if(score>0&& score<1000){
		scoreTexture=loadTexture(renderer, "image/score1.bmp");
	}else{
		if(score>1000&& score<1500){
			scoreTexture=loadTexture(renderer, "image/score2.bmp");
		}
		else{
			if(score>1500&& score<2000){
				scoreTexture=loadTexture(renderer, "image/score3.bmp");
			}else{
				if(score>2000&& score<3000){
					scoreTexture=loadTexture(renderer, "image/score4.bmp");
				}else{
					if(score>3000&& score<4000){
						scoreTexture=loadTexture(renderer, "image/score5.bmp");
					}else{
						if(score>4000&& score<5000){
							scoreTexture=loadTexture(renderer, "image/score6.bmp");
						}else{
							if(score>5000&& score<6000){
								scoreTexture=loadTexture(renderer, "image/score7.bmp");
							}else{
								if(score>6000&& score<7000){
									scoreTexture=loadTexture(renderer, "image/score8.bmp");
								}else{
									if(score>7000&& score<8000){
										scoreTexture=loadTexture(renderer, "image/score9.bmp");
									}else{
										if(score>8000&& score<10000){
											scoreTexture=loadTexture(renderer, "image/score10.bmp");
										}else{
											if(score>10000){
												scoreTexture=loadTexture(renderer, "image/score11.bmp");
											}
										}
									}
								}
							}
						}
					}
				}
			}
			
		}
	}
	
	//SDL_Texture*loseTexture=loadTexture(renderer, "image/gameover.bmp");
	SDL_RenderCopy(renderer,scoreTexture,NULL,&desRect);
	SDL_RenderPresent(renderer);
    //waitUntilKeyPressed();
}




