#ifndef _BOARD_
#define _BOARD_

#include "parts.h"


#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 16
#define BOARD_POSITION 320
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5

class Board{
public:
    Board (Parts *pParts,int pScreenHeight);
    int GetX_PosInPixels(int pPos);
    int GetY_PosInPixels(int pPos);
    bool isFreeBlock(int pX,int pY);
    bool isPossibleMovement(int pX,int pY,int pPart, int pRotation);
    void StorePiece(int pX,int pY,int pPart, int pRotation);
    void DeletePossibleLines();
    bool isGameOver();
    int getPoints() const { return this->points;}
    int bestScore(int currentPosition);    

private:
    enum {POS_FREE, POS_FILLED};      //POS_FREE - Free position on board, POS_Filled = filled possitions
    int mBoard [BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the parts
    Parts *mParts;
    int mScreenHeight;
    void InitBoard();
    void DeleteLine(int pY);
    int points = 0;

};   
#endif
