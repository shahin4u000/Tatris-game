#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include "time.h"
#include "conio.h"
//#include "utility"

/*---------------------------------------------------------------------
            Function
----------------------------------------------------------------------*/
int randomBlockGenerator();
unsigned int GetField( unsigned int PosX , unsigned int PosY );
bool isCoolidable (int x1, int y1);
bool RotateTetrisBlock(int);
int move(int movement);
void InitBoard();
void display();
void makeBlock();
bool gameOver();
/*---------------------------------------------------------------------
            Time delay function
----------------------------------------------------------------------*/


void systemPause () {
    struct timespec timeOut,remains;

    timeOut.tv_sec = 0;
    timeOut.tv_nsec = 900000000; /* 7 milliseconds */

    nanosleep(&timeOut, &remains);

};
/*---------------------------------------------------------------------
            Global variable
----------------------------------------------------------------------*/

int a=1;
int randNum[2];
int x=4,y=0; //cordinates
int rotateTemp[4][4]={0};
using namespace std;
int gameField[17][22];
int temp[17][22]={0};

enum Movement_E
{
    MoveLeft_e=1 , MoveRight_e,
    RotateTetrisBlock_e , RotateCounterClockwise_e,
    Release_e=0
};

/*---------------------------------------------------------------------
            empty block will be filled randomly
----------------------------------------------------------------------*/


int block[2][4][4]= {
    {
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0}
    },
    {
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0}
    }

};

/*---------------------------------------------------------------------
            tetris gaming block
----------------------------------------------------------------------*/

int tetrisBlock[7][5][5]={
    {
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    },
    {
        { 0, 0, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 0 },
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
        { 0, 1, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 }
    }
};

/*---------------------------------------------------------------------
            Main
----------------------------------------------------------------------*/
int main ()
{


    randomBlockGenerator();
    InitBoard();
    makeBlock();

    // gameloop
    //a should be a gameover condition and should add end of the game.
    while (!gameOver()) {

        display();

        int movement1;
        cin>>movement1;

        move(movement1);

        if(isCoolidable(x,y+1)  )
        {


            for(int i=0;i<17;i++)
            {
                for(int j=0;j<22;j++) {temp[i][j]=gameField[i][j];}
            }

            for (int i=0;i<4;i++)
            {
                for (int j=0;j<4;j++){
                    rotateTemp[i][j]=block[1][i][j];

                }
            }
            randomBlockGenerator();
            for (int i=0;i<4;i++)
            {
                for (int j=0;j<4;j++){
                    block[0][i][j]= rotateTemp[i][j];

                }
            }
            x=4,y=0;


            if(!gameOver()) {makeBlock();};
        }
    }
    move(5);
    for (int i=0;i<3;i++){
        systemPause();
    display();
    cout<<endl;
    cout<<"Game Over !!!\n";}





    return 0;
}
/*---------------------------------------------------------------------
            randomBlockGenerator()
----------------------------------------------------------------------*/
int randomBlockGenerator()
{
    srand (time(0));
    for(int i =0;i<2;i++)
    {
        randNum[i]=rand()%7;

    }

    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            block[0][i][j]=tetrisBlock[randNum[0]][i][j];
            block[1][i][j]=tetrisBlock[randNum[1]][i][j];
        }
    }

    return randNum[0];
}

/*---------------------------------------------------------------------
            InitBoard()
----------------------------------------------------------------------*/

void InitBoard()
{
    //Play Ground design (from o--16(x),0--16(Y))

    for(int i=0;i<17;i++)
    {
        for (int j=0;j<17;j++)
        {
            if(j==0 || j==11)
            {
                if(i<4)
                {
                    gameField[i][j]=3;
                    temp[i][j]=3;

                }
                else {gameField[i][j]=5; temp[i][j]=5;}
            }
            else if(i==16 &&j<11 ) {gameField[i][j]=5; temp[i][j]=5;}


            else {gameField[i][j]=0; temp[i][j]=0;}
        }
    }

    // small box design

    for(int i=0;i<17;i++)
    {
        for (int j=16;j<22;j++)
        {
            if((j==16 || j==21) && i<6)
            {
                gameField[i][j]=3;
            }


            else if((i==0 || i==5) && i<6)
            {
                gameField[i][j]=3;
            }


            else  gameField[i][j]=0;

        }
    }


}


void makeBlock()
{

    for(int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {gameField[i+y][j+x]=temp[i+y][j+x]+ block[0][i][j];}
    }
    //Sub field initialize with block
    for(int i=0;i<6;i++)
    {
        for (int j=16;j<22;j++)
        {
            if((j>16 && j<21) && (i>0 && i<5)){
                gameField[i][j]=block[1][i-1][j-17];}
        }
    }

}

void display(){
    system("cls");

    //*
    for(int i=0;i<17;i++)
    {
        for (int j=0;j<22;j++)
        {
            switch (gameField[i][j]) {
            case 0:
                cout<<" ";
                break;
            case 1:
                cout<<"0";
                break;
            case 3:
                cout<<"#";
                break;
            case 5:
                cout<<"x";
                break;
            }
            if(j==21) cout<<endl;

        }
    }//*/

    cout<<"\n1.Move Left        2.Move right \n";

    cout<<"3.Rotate clockwise 4.Rotate anti clockwise    5.Down\n";


    /*   For dispaly arrray checking
    for(int i=0;i<17;i++)
    {
        for (int j=0;j<22;j++)
        {
            cout<<gameField[i][j];if(j==21) cout<<endl;}}
    cout<<endl<<"temp:\n";
    for(int i=0;i<17;i++)
    {
        for (int j=0;j<22;j++)
        {
            cout<<temp[i][j];if(j==21) cout<<endl;}} //*/
}

int move ( int movement )
{

    switch (movement) {
    case 1:
        if (!isCoolidable(x-1,y)){
            GetField(x-1,y);}
        break;
    case 2:
        if (!isCoolidable(x+1,y)){
            GetField(x+1,y);}
        break;
    case 3:
        RotateTetrisBlock(1);
        break;

    case 4:
        RotateTetrisBlock(2);
        break;
    case 5:
        if (!isCoolidable(x,y+1)){
            GetField(x,y+1);}

        break;


    }
    return 0;
}

unsigned int GetField( unsigned int PosX , unsigned int PosY )
{

    for (int i =0;i<4;i++){
        for(int j=0;j<4;j++){

            gameField[y + i][x + j]-=block[0][i][j];
        }
    }
    x=PosX; y=PosY; //updating coordinate

    for (int i =0;i<4;i++){
        for(int j=0;j<4;j++){

            gameField[y + i][x + j]+=block[0][i][j];

        }

    }


    return 0;
}


bool isCoolidable (int x1,int y1)
{
    /*  cout<<x1<<y1<<endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
cout<<block[0][i][j];
        }
    cout<<endl;}
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
cout<<temp[y1 + i][x1 + j];
        }
    cout<<endl;}

*/
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[0][i][j] && (temp[y1 + i][x1 + j] != 0))
            {
                //cout<<"T"<<endl;
                return true;

            }
        }
    }

    return false;
}


bool RotateTetrisBlock(int rotateDirection)
{
    //for Clock wise  block rotation
    if(rotateDirection==1){

        for(int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                rotateTemp[i][j] = block[0][i][j];
                //rotateTemp[i][k]=block[0][j][i];
                //rotateTemp[i][k];
            }
        }
        for(int i=0;i<4;i++){
            for (int k=0,j=3;k<4,j>=0;k++,j--){

                block[0][i][k]=rotateTemp[j][i];
                //rotateTemp[i][k]=block[0][j][i];
                //rotateTemp[i][k];
            }
        }
        if (isCoolidable(x,y))
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    block[0][i][j] = rotateTemp[i][j];
                }
            }
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                gameField[y + i][x + j] -= rotateTemp[i][j];
                gameField[y + i][x + j] += block[0][i][j];
            }
        }

        display();
    }

    //for Counter Clock wise  block rotation
    else {

        for(int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                rotateTemp[i][j] = block[0][i][j];
                //rotateTemp[i][k]=block[0][j][i];
                //rotateTemp[i][k];
            }
        }
        for(int i=0;i<4;i++){
            for (int j=3;j>=0;j--){

                block[0][i][j]=rotateTemp[j][3-i];
                //rotateTemp[i][k]=block[0][j][i];
                //rotateTemp[i][k];
            }
        }
        if (isCoolidable(x,y))
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    block[0][i][j] = rotateTemp[i][j];
                }
            }
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                gameField[y + i][x + j] -= rotateTemp[i][j];
                gameField[y + i][x + j] += block[0][i][j];
            }
        }

        display();
    }

    return false;
}

bool gameOver ()
{
    for (int i=0;i<3;i++){
        for (int j=0;j<9;j++)
        {   cout<<temp[i+1][j+1];

            if(temp[i+1][j+1]!=0 ) {return true;}

        }
    }
    return false;
}
