
#include "include/IO.h"
#include <cstring>



static SDL_Surface *mScreen;
static SDL_Surface *screen = SDL_SetVideoMode(640,480,0,SDL_HWSURFACE | SDL_DOUBLEBUF);
static SDL_Surface *BestScore = SDL_SetVideoMode(640,480,0,SDL_HWSURFACE | SDL_DOUBLEBUF);
static Uint32 mColors[COLOR_MAX] = {0x000000ff,
                                    0xff0000ff,0x00ff00ff, 0x0000ffff,
                                    0x00ffffff,0xff00ffff,0xffff00ff,
                                    0xffffffff};

IO::IO(){
    InitGraph();
}

 void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC){
     boxColor(mScreen,pX1,pY1,pX2,pY2-1,mColors[pC]);

 }
 void IO::ClearScreen (){
boxColor(mScreen,0,0,mScreen->w-1,mScreen->h-1,mColors[BLACK]);

 }
 int IO::GetScreenHeight(){
        return mScreen->h;
 }

 int IO::Pollkey(){
     SDL_Event evnt;
     while(SDL_PollEvent(&evnt))
     {
         switch(evnt.type){
             case SDL_KEYDOWN:
             return evnt.key.keysym.sym;
             case SDL_QUIT:
             exit(3);
         }

     }
     return -1;
 }
 int IO::Getkey()
 {
     SDL_Event evnt;
     while(true)
     {
         SDL_WaitEvent(&evnt);
         if(evnt.type == SDL_KEYDOWN)
         break;
         if(evnt.type == SDL_QUIT)
         exit(3);
     };
     return evnt.key.keysym.sym;
 }
 int IO::IsKeyDown(int pKey)
 {
     Uint8 *mKeytable;
     int mNumkeys;
     SDL_PumpEvents();
     mKeytable = SDL_GetKeyState(&mNumkeys);
     return mKeytable[pKey];
 }
 void IO::UpdateScreen(){
    SDL_Flip(mScreen);        
    SDL_Flip(screen);
    SDL_Flip(BestScore);
 }

void IO::DrawPoints(int points){
    std::string strMain = "This game your score is: " + std::to_string(points);
     char * cstr = new char [strMain.length()+1];
    std::strcpy (cstr,strMain.c_str());

    TTF_Init();
    TTF_Font* fnt = TTF_OpenFont("./ARIAL.ttf",14);

    SDL_Color forgr = {255,255,255};
     SDL_Color backgr = {0,0,255};
     SDL_Rect textLocation = {430,200,0,0};
    
    SDL_Surface* textSurface = TTF_RenderText_Shaded(fnt,cstr,forgr,backgr);
    
    //SDL_FillRect (screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(textSurface,NULL,screen,&textLocation);

     
        delete[] cstr;
     cstr = NULL;
     
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(fnt);
    TTF_Quit();
          
}

void IO::DrawBestScore(int points){
    std::string strMain = "Your best score is: " + std::to_string(points);
     char * cstr = new char [strMain.length()+1];
    std::strcpy (cstr,strMain.c_str());

    TTF_Init();
    TTF_Font* fnt = TTF_OpenFont("./ARIAL.ttf",14);

    SDL_Color forgr = {255,255,255};
     SDL_Color backgr = {0,0,255};
     SDL_Rect textLocation = {440,160,0,0};
    
    SDL_Surface* textSurface = TTF_RenderText_Shaded(fnt,cstr,forgr,backgr);
    
    //SDL_FillRect (screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(textSurface,NULL,BestScore,&textLocation);

     
    delete[] cstr;
     cstr = NULL;
     
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(fnt);
    TTF_Quit();
}

int IO::InitGraph()
{
    const SDL_VideoInfo *info;
    Uint8 video_bpp;
    Uint32 videoFlags;
    
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        fprintf(stderr,"Couldn`t initialize SDL: %s\n",SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    info=SDL_GetVideoInfo();
    if(info->vfmt->BitsPerPixel>8){
        video_bpp = info->vfmt->BitsPerPixel;
    }
    else{
        video_bpp = 16;
    }
    videoFlags=SDL_SWSURFACE | SDL_DOUBLEBUF;
    if((mScreen=SDL_SetVideoMode(640,480,video_bpp,videoFlags)) == NULL){
        fprintf(stderr, "Couldn`t set %ix%i video mode: %s\n",640,480,SDL_GetError());
        return 2;
    }
  //TTF_Init();
    return 0;

 }
 
