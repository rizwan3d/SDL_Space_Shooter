#include <SDL.h>
#include<iostream>

using namespace std;

////////  Const for windows Size and Title  ////////////
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define WINDOW_CAPTION "Falling Blocks"
/////////////////////////////////////////////


//////  Global Variable    ///////////////////

SDL_Window * window;					// Windows Variable
SDL_Surface * screenSurface;			// Varibale that point to inner Contant of Window 
SDL_Event event;						// Varibale That hold info about Keybord button press , Mouser etc

bool gameRunning = true;                // valible that Show Game is running or not

string basPath = SDL_GetBasePath();

///Plane Valiable
int Px = 360 , Py = 500;
string planeFilePath = basPath + "plane.bmp";
SDL_Surface* Plane = SDL_LoadBMP(planeFilePath.c_str());

///Background Valiable
string BackgroundFilePath = basPath + "background.bmp";
SDL_Surface* Background = SDL_LoadBMP(BackgroundFilePath.c_str());

///GameOver Valiable
string GameOverFilePath = basPath + "GameOver.bmp";
SDL_Surface* GameOver = SDL_LoadBMP(GameOverFilePath.c_str());

//astroid Valiable
string astroidFilePath = basPath + "astroid.bmp";
SDL_Surface* astroid = SDL_LoadBMP(astroidFilePath.c_str());

int A1Y = -82;
int A2Y = -82;
int A3Y = -82;
int A4Y = -82;

int TimeForA = 0;

/////////////////////////////////////////////

/////// Bulate ////////////////////////

int PositionsB[30][2];
int LstIndex = 0;

string BulateFilePath = basPath + "b.bmp";
SDL_Surface* Bulate = SDL_LoadBMP(BulateFilePath.c_str());


////////////////////////////////////////////


//////  Functions Signatiures   ///////////////////

void MakeWindow();    // funation to make Window for game 

					  // Draw Image on Screen
void drawSprite(SDL_Surface* imageSurface,
	SDL_Surface* screenSurface,
	int srcX, int srcY,
	int dstX, int dstY,
	int width, int height);

void AstridDrawAndAnimation();	// Load Astroid and Animate it

void KeybordInput();   //anyting haped with keybord or mouse

bool collision(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2);  //collision dection
/////////////////////////////////////////////


void bullet() {
	for (int i = 0; i < 30; i++) {
		if (PositionsB[i][0] != 0) {
			PositionsB[i][1]--;
			drawSprite(Bulate, screenSurface, 0, 0, PositionsB[i][0], PositionsB[i][1], 9, 37);
			if (PositionsB[i][1] < -38) {
				PositionsB[i][0] = 0;
			}
			if (collision(010, A1Y, 89, 82, PositionsB[i][0], PositionsB[i][1], 9, 37)) { A1Y = -83; PositionsB[i][0] = 0; }
			if (collision(200, A2Y, 89, 82, PositionsB[i][0], PositionsB[i][1], 9, 37)) { A2Y = -83; PositionsB[i][0] = 0; }
			if (collision(400, A3Y, 89, 82, PositionsB[i][0], PositionsB[i][1], 9, 37)) { A3Y = -83; PositionsB[i][0] = 0; }
			if (collision(660, A4Y, 89, 82, PositionsB[i][0], PositionsB[i][1], 9, 37)) { A4Y = -83; PositionsB[i][0] = 0; }
		}
	}
}

int main(int argc,char* args[]) {

	MakeWindow();

	while (gameRunning)
	{
		//Fill the surface white  or Clear Window
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

		//load BackGrount
		drawSprite(Background, screenSurface, 0, 0, 0, 0, 800, 600);

		AstridDrawAndAnimation();

		KeybordInput();

			// plane collide with any astrid break game loop
		if (	   collision(10,  A1Y, 89, 82, Px, Py, 99, 75)
				|| collision(200, A2Y, 89, 82, Px, Py, 99, 75)
			    || collision(400, A3Y, 89, 82, Px, Py, 99, 75)
			    || collision(660, A4Y, 89, 82, Px, Py, 99, 75)
			)
			gameRunning = false;
		bullet();
		//Draw a Player Plane at Px and Py position
		drawSprite(Plane, screenSurface, 0, 0, Px, Py, 99, 75);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}

	while (true)
	{
		//Fill the surface white  or Clear Window
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
		//load BackGrount
		drawSprite(Background, screenSurface, 0, 0, 0, 0, 800, 600);
		KeybordInput();
		//Draw GameOver Image
		drawSprite(GameOver, screenSurface, 0, 0, 137, 260, 558, 83);
		//Update the surface
		SDL_UpdateWindowSurface(window);
	}

	return 0;
}


void MakeWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		window = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window != NULL) {
			screenSurface = SDL_GetWindowSurface(window);
		}		
	}
}

void drawSprite(SDL_Surface* imageSurface,
	SDL_Surface* screenSurface,
	int srcX, int srcY,
	int dstX, int dstY,
	int width, int height)
{
	SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 0xFF, 0xFF, 0xFF));

	SDL_Rect srcRect;
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = width;
	srcRect.h = height;

	SDL_Rect dstRect;
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = width;
	dstRect.h = height;

	SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
}

void AstridDrawAndAnimation() {
	

	// Load astroid at X = 0 and Y = A1y
	drawSprite(astroid, screenSurface, 0, 0, 10, A1Y, 89, 82);
	A1Y++; // chage y postion if 1st astroid
	if (A1Y > 600) // astrid getout form screen it take to it's starting point 
		A1Y = -83;

	if (TimeForA > 200) {  // if time value is grater than 200 than load second astroid 
		drawSprite(astroid, screenSurface, 0, 0, 200, A2Y, 89, 82);
		A2Y++;
		if (A2Y > 600)
			A2Y = -83;
	}

	if (TimeForA > 100) { // same as above
		drawSprite(astroid, screenSurface, 0, 0, 400, A3Y, 89, 82);
		A3Y++;
		if (A3Y > 600)
			A3Y = -83;
	}

	if (TimeForA > 150) {// same as above
		drawSprite(astroid, screenSurface, 0, 0, 660, A4Y, 89, 82);
		A4Y++;
		if (A4Y > 600)
			A4Y = -83;
	}

	if (TimeForA <= 200) // stop time counting if it become larger than 200
		TimeForA++;     // increase in time
}

void KeybordInput(){

	if (SDL_PollEvent(&event))  // check anyting haped with keybord or mouse
	{
		if (event.type == SDL_QUIT)  // ckeck id close buton preses
		{
			gameRunning = false; // end game loop
			if (!gameRunning) {
				exit(0);
			}
		}
		if (event.type == SDL_KEYDOWN)  // if any keybord button get pressed
		{
			if (event.key.keysym.sym == SDLK_LEFT) // if Left Arrow pressed
			{
				Px -= 10;  //chage the  x position of plane to left
			}
			if (event.key.keysym.sym == SDLK_RIGHT) // if Right Arrow pressed
			{
				Px += 10; //chage the  x position of plane to right
			}
			if (event.key.keysym.sym == SDLK_SPACE) // if Right Arrow pressed
			{
				PositionsB[LstIndex][0] = Px + 45;
				PositionsB[LstIndex][1] = Py;
				LstIndex++;
				if (LstIndex > 30) {
					LstIndex = 0;
				}
			}
		}

	}

}

bool collision(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2) {
	//Let's examine the x axis first:
	//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
	if ((x1 >= x2 && x1 <= (x2 + w2)) ||
		((x1 + w1) >= x2 && (x1 + w1) <= (x2 + w2))) {
		//Now we look at the y axis:
		if ((y1 >= y2 && y2 <= (y2 + h2)) ||
			((y1 + h1) >= y2 && (y1 + h1) <= (y2 + h2))) {
			//The sprites appear to overlap.
			return true;
		}
	}
	//The sprites do not overlap:
	return false;
}