#include <iostream>
#include "include/game.h"


int main(){
    IO mIO;
    int mScreenHeight = mIO.GetScreenHeight();
    Parts mParts;
    Board mBoard(&mParts,mScreenHeight);
    Game mGame(&mBoard,&mParts,&mIO,mScreenHeight);
    
    
unsigned long mTime1 = SDL_GetTicks();
    while(!mIO.IsKeyDown(SDLK_ESCAPE))
    {
     
     
        mIO.ClearScreen();
        mGame.DrawScene();
       
        mIO.DrawPoints(mBoard.getPoints());
        mIO.DrawBestScore(mBoard.bestScore(mBoard.getPoints()));
        mIO.UpdateScreen();
        

        int mKey = mIO.Pollkey();

        switch(mKey){
            case(SDLK_RIGHT):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX+1,mGame.mPosY,mGame.mPart,mGame.mRotation)){
                    mGame.mPosX++;
                }
                break;
            }
            case(SDLK_LEFT):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX -1,mGame.mPosY,mGame.mPart,mGame.mRotation))
                {mGame.mPosX--;
                break;}

            }
            case(SDLK_DOWN):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX,mGame.mPosY +1 ,mGame.mPart,mGame.mRotation))
                {++mGame.mPosY;
                break;}
            }
            case(SDLK_x):
            {
                while(mBoard.isPossibleMovement(mGame.mPosX,mGame.mPosY,mGame.mPart,mGame.mRotation))
                {
                    mGame.mPosY++;
                }
                mBoard.StorePiece(mGame.mPosX,mGame.mPosY-1,mGame.mPart,mGame.mRotation);
                mBoard.DeletePossibleLines();
                

                if (mBoard.isGameOver()){
                    mIO.Getkey();
                    exit(0);
                }
                mGame.CreateNewPiece();
                break;
            }
            case(SDLK_z):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX,mGame.mPosY,mGame.mPart,(mGame.mRotation+1)%4)){
                    mGame.mRotation = (mGame.mRotation+1)%4;
                    break;
                }
            }
        }
        unsigned long mTime2 = SDL_GetTicks();
        if((mTime2 -mTime1)>WAIT_TIME)
        {
            if(mBoard.isPossibleMovement(mGame.mPosX,mGame.mPosY+1,mGame.mPart,mGame.mRotation))
            {
                mGame.mPosY++;
            }
            else{
                mBoard.StorePiece(mGame.mPosX,mGame.mPosY,mGame.mPart,mGame.mRotation);
                mBoard.DeletePossibleLines();

                if(mBoard.isGameOver())
                {
                    mIO.Getkey();
                    exit(0);
                }
                mGame.CreateNewPiece();
            }
            mTime1 = SDL_GetTicks();

        }
        
    }
    return 0;
}