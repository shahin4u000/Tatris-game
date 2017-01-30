

#ifndef MYDERIVEDCLASS_H
#define MYDERIVEDCLASS_H

#include "Interfaces.h"
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;


class myIBoard :public IBoard
{
protected:

    int x=4,y=0; //cordinates
public:

    myIBoard();
    void InitBoard() ;
    
    unsigned int GetField( unsigned int PosX , unsigned int PosY ) const  ;
    
    void Move ( Movement_E Movement )  ;
    
    bool IsFinished() const ;
    
    BlockType_E GetNextBlockType() const ;


    unsigned int GetPoints() const ;
    
    unsigned int GetRemovedRows() const  ;
    
    void updateGameField(unsigned int PosX, unsigned int PosY, int arr[17][22] );
    
    bool RotateTetrisBlock(int rotateDirection);

    int getTheNextBlock();

   // void display();

    void clear_screen();

    int filledRowCheck(int b);

    void initiallyBlockGenerate();

    int certainGetRemovedRow();

    int certainGetPoints();
    int gameField[17][22]; // it is a 2D array. game will be played by updating the field
private:
    bool isFilled;       //ei 2ta funtion a deya jai. check again
    int c=0;            // if C==10,means 10 consequtive row has some value,means row is filled.
    int totalPoints=0; //begaining it is 0 and will be updated if row is filled
    int noOfRemovedRow=0;   //begaining it is 0 and will be updated if row is filled
    int totalRow;
    int temp[17][22];   // after releasing the block it will contain the main Game Board
                       //and will be used to check if any collision occurs with the current block  moves.
    vector <int> filledRow;   // it will contain the number of filled row for certain time
    int block[2][4][4]; // block [0][4][4], block [1][4][4]
                        //block [0][4][4] will be showed middle of the game board.
                       // block [1][4][4] will be showed as next block
    int rotateTemp[4][4];

    /*---------------------------------------------------------------------
                tetris gaming block
    ----------------------------------------------------------------------*/

    int tetrisBlock[7][4][4]={
        {
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 1, 1, 1, 1 },
                { 0, 0, 0, 0 }
        },
        {
                { 0, 0, 0, 0 },
                { 0, 0, 1, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 0, 0 }
        },
        {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 0, 0 }
        },
        {
                { 0, 0, 0, 0 },
                { 1, 0, 0, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 0, 0 }
        },
        {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 1, 1, 0, 0 },
                { 0, 0, 0, 0 }
        },
        {
                { 0, 0, 0, 0 },
                { 1, 1, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 0, 0, 0 }
        },
        {
                { 0, 0, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 0, 0 }
        }
    };



};


#endif // MYDERIVEDCLASS_H
