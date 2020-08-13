#include "include/game.h"



Game::Game(Board *pBoard, Parts *pParts, IO *pIO, int pScreenHeight)
{
    mScreenHeight = pScreenHeight;
    mBoard = pBoard;
    mParts = pParts;
    mIO = pIO;

    InitGame();
}

int Game::GetRand(int pA,int pB)
{
    return rand() %(pB - pA +1) +pA;
}

void Game::InitGame()
{
    srand((unsigned int)time(NULL));
    mPart = GetRand(0,7);
    mRotation = GetRand(0,3);
    mPosX =(BOARD_WIDTH/2)+ mParts->GetX_InitialPosition(mPart,mRotation);
    mPosY = mParts->GetY_InitialPosition(mPart,mRotation);

    mNextPart = GetRand(0,7);
    mNextRotation =GetRand(0,3);
    mNextPosX = BOARD_WIDTH +5;
    mNextPosY = 5;


}

void Game::CreateNewPiece()
{
    mPart = mNextPart;
    mRotation=mNextRotation;
    
    mPosX =(BOARD_WIDTH/2)+ mParts->GetX_InitialPosition(mPart,mRotation);
    mPosY = mParts->GetY_InitialPosition(mPart,mRotation);

    mNextPart = GetRand(0,7);
    mNextRotation =GetRand(0,3);
}

void Game::DrawPart(int pX , int pY , int pPart, int pRotation)
{
    color mColor;
    int mPixelsX = mBoard->GetX_PosInPixels(pX);
    int mPixelsY = mBoard->GetY_PosInPixels(pY);

    for(int i = 0; i <PIECE_BLOCKS;++i)
    {
        for(int j = 0; j<PIECE_BLOCKS;j++){
            switch(mParts->GetBlockType(pPart,pRotation,j,i))
            {
                case 1:mColor = GREEN;break;
                case 2:mColor = BLUE;break;
            }
            if(mParts->GetBlockType(pPart,pRotation,j,i)!= 0){
            mIO->DrawRectangle(mPixelsX + i *BLOCK_SIZE,
                                mPixelsY+j *BLOCK_SIZE,
                                (mPixelsX + i *BLOCK_SIZE)+BLOCK_SIZE-1,
                                (mPixelsY+ j*BLOCK_SIZE)+BLOCK_SIZE -1,
                                mColor);
            }
        }
    }

}

void Game::DrawBoard()
{
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH/2)-1);
    int mX2 = BOARD_POSITION + (BLOCK_SIZE *(BOARD_WIDTH /2));
    int mY = mScreenHeight - (BLOCK_SIZE*BOARD_HEIGHT);

    mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH , mY,mX1,mScreenHeight -1, BLUE);
    mIO->DrawRectangle(mX2,mY,mX2 + BOARD_LINE_WIDTH,mScreenHeight -1 ,BLUE);
    mX1+=1;


    for(int i = 0 ; i<BOARD_WIDTH;++i){
        for(int j = 0 ; j<BOARD_HEIGHT;++j){
            if(!mBoard->isFreeBlock(i,j)){
                mIO->DrawRectangle(mX1 + i*BLOCK_SIZE,
                                        mY+j*BLOCK_SIZE,
                                        (mX1 + i * BLOCK_SIZE)+BLOCK_SIZE-1,
                                        (mY+ j *BLOCK_SIZE)+BLOCK_SIZE-1,
                                        RED);

            }
        }

    }
}

void Game::DrawScene()
{
    DrawBoard();
    DrawPart(mPosX,mPosY,mPart,mRotation);
    DrawPart(mNextPosX,mNextPosY,mNextPart,mNextRotation);
}