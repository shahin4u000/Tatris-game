#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include "time.h"
#include <vector>
#include "conio.h"
//#include "utility"

void clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}
/*---------------------------------------------------------------------
            Global variable
----------------------------------------------------------------------*/
bool isFilled; //ei 2ta funtion a deya jai. check again
int c=0;
bool a=false;
int totalPoints=0;

int randNum[2];
int x=4,y=0; //cordinates
int rotateTemp[4][4]={0};
using namespace std;
int gameField[17][22];
int temp[17][22]={0};
vector <int> filledRow;
vector <int> tempFilledRow4Display;

int filledRowCheck(int b)
{

    for(unsigned int i=0;i<filledRow.size();i++)
    {
        if(b==filledRow[i]) {return filledRow[i];}
    }

    return 0;
}
enum Movement_E
{
    MoveLeft_e=1 , MoveRight_e ,
    RotateClockwise_e , RotateCounterClockwise_e ,
    Release_e
};
Movement_E moveIndex;
enum BlockType_E
{
    I_Block_e , L_Block_e , T_Block_e , J_Block_e ,
    S_Block_e , O_Block_e , Z_Block_e
};

/*---------------------------------------------------------------------
            Function
----------------------------------------------------------------------*/
int randomBlockGenerator();
unsigned int GetField( unsigned int PosX , unsigned int PosY );
bool isCoolidable (int x1, int y1);
bool RotateTetrisBlock(int);
void move(Movement_E Movement);
void InitBoard();
void display();
void makeBlock();
bool isFinished();
int GetRemovedRows();
unsigned int GetPoints();



/*---------------------------------------------------------------------
            Time delay function
----------------------------------------------------------------------*/


void systemPause () {
    struct timespec timeOut,remains;

    timeOut.tv_sec = 0;
    timeOut.tv_nsec = 500000000; /* 7 milliseconds */

    nanosleep(&timeOut, &remains);

}


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

int tetrisBlock[7][4][4]={
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
    //a should be a isFinished condition and should add end of the game.
    while (!isFinished()) {



        //        while(!isCoolidable(x,y+1))
        //        {

        unsigned char userInput;
        if(kbhit())
        {

            userInput=getch();

            switch (userInput)
            {
            case 75:  //75
                move(MoveLeft_e);
                break;
            case 77:  //77
                move(MoveRight_e);
                break;
            case 'x':
                while(!isCoolidable(x,y+1)){
                    move(Release_e);display();}
                break;
            case 'a':
                move(RotateCounterClockwise_e);
                break;
            case 'd':
                move(RotateClockwise_e);
                break;

            }

        }
        else
        {
            move(Release_e);display(); systemPause();
        }
        //}




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


            if(!isFinished()) {makeBlock();};
            a=true;
            // GetRemovedRows();
            GetPoints();

        }

    }

move(Release_e);
for (int i=0;i<5;i++){
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

    return 0;}

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


            else if((i==0 || i==5) )
            {
                gameField[i][j]=3;
            }


            else if(i==8)
            {
                gameField[i][16]=6;

            }
            else if(i==9)
            {
                gameField[i][16]=7;

            }
            else if(i==11)
            {
                gameField[i][16]=8;

            }
            else if(i==12)
            {
                gameField[i][16]=9;

            }
            else if(i==13)
            {
                gameField[i][16]=10;

            }

            else
            {
                gameField[i][j]=0;
            }
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

    clear_screen();

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
            case 6:
                cout<<"Points:";
                break;
            case 7:
                cout<<GetPoints();
                a= false;
                break;
            case 8:
                cout<<"Removed";
                break;
            case 9:
                cout<<" Rows:";
                break;
            case 10:
                for(int i=0;i<tempFilledRow4Display.size();i++)
                {
                    cout<< tempFilledRow4Display[i] <<" ";
                }
                tempFilledRow4Display.clear();
            }
            if(j==21) cout<<endl;

        }


    }
    //*/

    cout<<"Move Left  ( <-- )\n";
    cout<<"Move right ( --> )\n";
    cout<<"Release    (  x  )\n";
    cout<<"Rotate Counter clockwise(a)\n";
    cout<<"Rotate clockwise (d)\n";


    //    //   For dispaly arrray checking
    //    for(int i=0;i<17;i++)
    //    {
    //        for (int j=0;j<22;j++)
    //        {
    //            cout<<gameField[i][j];if(j==21) cout<<endl;}}
    //    cout<<endl<<"temp:\n";
    //    for(int i=0;i<17;i++)
    //    {
    //        for (int j=0;j<22;j++)
    //        {
    //            cout<<temp[i][j];if(j==21) cout<<endl;}
    //    }
    //    cout<<"Row,point"<<GetRemovedRows()<<" "<<GetPoints();
    //    cout<<"kk:"<<kk;

}

void move ( Movement_E Movement )
{

    switch (Movement) {
    case MoveLeft_e:
        if (!isCoolidable(x-1,y)){
            GetField(x-1,y);}
        break;
    case MoveRight_e:
        if (!isCoolidable(x+1,y)){
            GetField(x+1,y);}
        break;
    case RotateClockwise_e:
        RotateTetrisBlock(1);
        break;

    case RotateCounterClockwise_e:
        RotateTetrisBlock(2);
        break;
    case Release_e:
        if (!isCoolidable(x,y+1)){
            GetField(x,y+1);}

        break;


    }

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
            for (int k=0, j=3;k<4,j>=0;k++,j--){

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

        //display();
    }

    //for Counter Clock wise  block rotation
    else {

        for(int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                rotateTemp[i][j] = block[0][i][j];

            }
        }
        for(int i=0;i<4;i++){
            for (int j=3;j>=0;j--){

                block[0][i][j]=rotateTemp[j][3-i];

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

        // display();
    }

    return false;
}


int GetRemovedRows()
{

    int totalRow;
    for (int i =1;i<17;i++){
        for(int j=1;j<12;j++){

            if(gameField[i][j]==0) {isFilled=false;}
            else if(gameField[i][j]==1) {isFilled=true;c++;}
        }

        if(isFilled && c==10)
        {
            filledRow.push_back(i);  isFilled=false;c=0; //may b c ta ei khane dorkar nai..without c check korte hobe.
        }
        c=0;
    }


    if(!filledRow.empty())
    {
        for (int i=15,k=15;i>=4,k>=4;i--,--k){
            for (int j=0;j<12;j++){
                if(k==filledRowCheck(k)) {--k ;if(k==filledRowCheck(k)){--k;if(k==filledRowCheck(k)){--k;}}}
                if(k!=filledRowCheck(k)){

                    gameField[i][j]=temp[k][j];

                }

            }
        }
    }
    totalRow=filledRow.size();
    if(totalRow){
        for (int i=4;i<4+totalRow;i++)
        { for (int j=1;j<10;j++)
            {
                gameField[i][j]=0;
                //cout<<i<<j;} cout<<endl;
            }
        }

        for(int i=4;i<16;i++)
        {
            for (int j=1;j<12;j++)
            {
                temp[i][j]=gameField[i][j];
            }
        }
    }

    isFilled=false;
    // filledRow.clear();
    return totalRow;
}

bool isFinished ()
{
    for (int i=0;i<3;i++){
        for (int j=0;j<9;j++)
        {
            if(temp[i+1][j+1]!=0 ) {return true;}

        }
    }
    return false;
}
unsigned int GetPoints()
{
    int tempRowNumb=0;
    if(a)
    {
        tempRowNumb= GetRemovedRows();
        for(int i=0;i<filledRow.size();i++)
        {
            tempFilledRow4Display.push_back(filledRow[i]);
        }
        filledRow.clear();

    }

    if(tempRowNumb){totalPoints+=100*tempRowNumb^2; }
    return totalPoints;
}
