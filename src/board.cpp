#include "include/board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Board::Board(Parts *pParts,int pScreenHeight)
{
    mScreenHeight = pScreenHeight;
    mParts = pParts;
    InitBoard();
}

void Board::InitBoard(){
    for(int i = 0; i<BOARD_WIDTH;i++){
        for(int j = 0; j<BOARD_HEIGHT;j++)
        {
            mBoard[i][j] =POS_FREE;
        }
    }
}

void Board::StorePiece(int pX, int pY, int pPart, int pRotation)
{
    for(int i = pX, i1=0; i<pX+PIECE_BLOCKS; i++,i1++){
        for(int j = pY, j1=0; j<pY+PIECE_BLOCKS;j++,j1++){
            if(mParts->GetBlockType(pPart,pRotation,j1,i1)!=0){
                mBoard[i][j] = POS_FILLED;
            }
        }
    }

}

bool Board::isGameOver()
{
    //if the first line has blocks = game over
    for(int i = 0; i<BOARD_WIDTH;i++)
    {
        if (mBoard[i][0] == POS_FILLED) return true;
    }
    return false;
}

void Board::DeleteLine(int pY)
{
    for(int j = pY ; j>0;j--)
    {
        for(int i = 0; i<BOARD_WIDTH;++i){
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
    points +=20;
    
}
void Board::DeletePossibleLines()
{
    
    for(int j = 0; j<BOARD_HEIGHT;++j)
    {
    
        int i = 0;
        while(i<BOARD_WIDTH)
        {
            if(mBoard[i][j] != POS_FILLED) break;
            i++;
        };
        if(i == BOARD_WIDTH){

            DeleteLine(j);

        }

    }
 
}

bool Board::isFreeBlock(int pX, int pY)
{
    if(mBoard[pX][pY] == POS_FREE){
         return true;
    }
    else{
        return false;
    }
}
//returns horizontal position of the block(in pixels) given like parameter
int Board::GetX_PosInPixels(int pPos){
return ((BOARD_POSITION -(BLOCK_SIZE*(BOARD_WIDTH/2)))+(pPos*BLOCK_SIZE));
}
// vertical in pixels
int Board::GetY_PosInPixels(int pPos)
{
    return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT))+(pPos* BLOCK_SIZE));
}
bool Board::isPossibleMovement(int pX, int pY, int pPart, int pRotation)
{
    for(int i1 = pX,i2=0; i1<pX+PIECE_BLOCKS; i1++,i2++)
    {
        for(int j1=pY, j2=0; j1<pY+PIECE_BLOCKS;j1++,j2++)
        {
            //5x5 bocks with the appropriate area in the board check.
            if(i1<0 || i1>BOARD_WIDTH || j1> BOARD_HEIGHT-1)
            {
                if(mParts->GetBlockType(pPart,pRotation,j2,i2) != 0)
                {
                    return false;
                }
            }
            //check for collision with block already in the map
            if(j1 >= 0)
            {
                if((mParts->GetBlockType(pPart,pRotation,j2,i2)!= 0)&& (!isFreeBlock(i1,j1))){
                    return false;
                }
            }
        }
    }
    //no collision
    return true;
}


int Board::bestScore(int CurrentPoints){

std::ofstream myFile;
std::string line;
std::ifstream openMyFile ("./bestScore.txt");

if(openMyFile.is_open()){
getline(openMyFile,line);
    
openMyFile.close();
}

int a = std::stoi(line);


if(CurrentPoints>a){
    myFile.open("./bestScore.txt");
    myFile<< CurrentPoints;
    myFile.close();
    return CurrentPoints;
}
else{
    myFile.close();
    return a;
    }
myFile.close();
return a;

}