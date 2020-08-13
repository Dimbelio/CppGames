#ifndef _GAME_
#define _GAME

#include "board.h"
#include "IO.h"
#include <time.h>
#define WAIT_TIME 700

class Game{
public:
    Game(Board *pBoard,Parts *pParts, IO *pIO, int pScreenHeight);
    void DrawScene();
    void CreateNewPiece();

    int mPosX, mPosY;
    int mPart, mRotation;

private:
    int mScreenHeight;
    int mNextPosX, mNextPosY;
    int mNextPart, mNextRotation;
  
    Board *mBoard;
    Parts *mParts;
    IO *mIO;
    
    int GetRand(int pA, int pB);
    void InitGame();
    void DrawPart(int pX, int pY,int pPart,int pRotation);
    void DrawBoard();

};


#endif