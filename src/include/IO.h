#ifndef _IO_
#define _IO_
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
//#pragma comment (lib, "SDL/lib/SDL.lib")
#include <SDL/SDL_ttf.h>
#include <string>


enum color {BLACK,RED,GREEN,BLUE,CYAN,MAGENTA,YELLOW,WHITE,COLOR_MAX};

class IO{
public:
IO ();
 void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
 void ClearScreen ();
 int GetScreenHeight();
 int InitGraph();
 int Pollkey();
 int Getkey();
 int IsKeyDown(int pKey);
    void UpdateScreen();

void DrawPoints(int a);
void DrawBestScore(int points);
};

#endif