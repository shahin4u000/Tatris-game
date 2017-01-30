#include "myDerivedCLass.h"
#include <time.h>



myIBoard::myIBoard()
{

}

void myIBoard::InitBoard()
{
    
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

    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            block[0][i][j]=tetrisBlock[GetNextBlockType()][i][j];
        }
    }

    //Initailly block Generate
    int rand1,rand2;

    srand(time(NULL));

    rand1=rand()%7;

    rand2=rand()%7;

    for(int i=0;i<4;i++)
    {for (int j=0;j<4;j++)
        {
        block [0][i][j]=tetrisBlock[rand1][i][j] ;
        block [1][i][j]=tetrisBlock[rand2][i][j] ;

        }
    }
    initiallyBlockGenerate();





    //    for(int i=0;i<4;i++)
    //    {
    //        for (int j=0;j<4;j++)
    //        {
    //            cout<<block[1][i][j];

    //        } cout<<endl;
    //    }
    //    updateGameField(3,0);
    //    cout<<endl;

   // display();
}

unsigned int myIBoard::GetField(unsigned int PosX, unsigned int PosY) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[0][i][j] && (temp[PosY + i][PosX + j] != 0))
            {
                //cout<<"T"<<endl;
                return 1;

            }
        }
    }

    return 0;
}

void myIBoard::Move(Movement_E Movement)
{
    switch (Movement) {
    case MoveLeft_e:
        if (!GetField(x-1,y))
        {
            updateGameField(x-1,y,gameField);

        }

        break;
    case MoveRight_e:
        if (!GetField(x+1,y))
        {
            updateGameField(x+1,y,gameField);
        }

        break;
    case RotateClockwise_e:
        RotateTetrisBlock(1);

        break;

    case RotateCounterClockwise_e:
        RotateTetrisBlock(2);

        break;
    case Release_e:
        while (!GetField(x,y+1))
        {
            updateGameField(x,y+1,gameField);
        }

        if(1 )
        {

            for(int i=0;i<17;i++)
            {
             for(int j=0;j<22;j++) {temp[i][j]=gameField[i][j];}
            }
            getTheNextBlock();

            x=4;y=0;
           if(!IsFinished()) {initiallyBlockGenerate();};

           certainGetRemovedRow();
         }

        break;


    }
}

bool myIBoard::IsFinished() const
{
    for (int i=0;i<3;i++){
        for (int j=0;j<10;j++)
        {
            if(temp[i+1][j+1]!=0 ) {return true;}

        }
    }
    return false;
}

int a=0;

BlockType_E myIBoard::GetNextBlockType() const
{

    srand (time(NULL));
    switch (rand()%7)
    {
    case 0:
        return I_Block_e;

        break;
    case 1:
        return L_Block_e;
        break;
    case 2:
        return T_Block_e;
        break;
    case 3:
        return J_Block_e;
        break;
    case 4:
        return S_Block_e;
        break;
    case 5:
        return O_Block_e;
        break;
    case 6:
        return Z_Block_e;
        break;
    }

}



unsigned int myIBoard::GetPoints() const
{
    return totalPoints;

}

unsigned int myIBoard::GetRemovedRows() const
{
    return noOfRemovedRow;
    
}
//after the move command updates the current game field
void myIBoard::updateGameField(unsigned int PosX, unsigned int PosY, int arr[][22])
{
    
    
    for (int i =0;i<4;i++){
        for(int j=0;j<4;j++){

            arr[y + i][x + j]-=block[0][i][j];
        }
    }
    x=PosX; y=PosY; //updating coordinate
    cout<<endl<<x<<y<<endl;
    
    for (int i =0;i<4;i++){
        for(int j=0;j<4;j++){

            arr[y + i][x + j]+=block[0][i][j];
        }
    }
    


}

bool myIBoard::RotateTetrisBlock(int rotateDirection)
{
    if(rotateDirection==1){

        for(int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                rotateTemp[i][j] = block[0][i][j];

            }
        }
        for(int i=0;i<4;i++){
            for (int k=0, j=3;k<4,j>=0;k++,j--){

                block[0][i][k]=rotateTemp[j][i];

            }
        }
        if (GetField(x,y))
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
        if (GetField(x,y))
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


    }
    
}

int myIBoard::getTheNextBlock()
{



   for (int i=0;i<4;i++){
       for(int j=0;j<4;j++){

           block[0][i][j]=block[1][i][j];
           block[1][i][j]=tetrisBlock[ GetNextBlockType()][i][j];
       }
   }



}


void myIBoard::clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Assume Linux
    std::system ("clear");
#endif
}

//this function will say which coloum is filled with block
int myIBoard:: filledRowCheck(int b)
{

    for(unsigned int i=0;i<filledRow.size();i++)
    {
        if(b==filledRow[i]) {return filledRow[i];}
    }

    return 0;
}

void myIBoard::initiallyBlockGenerate()
{  // getTheNextBlock();

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
int myIBoard::certainGetRemovedRow()
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

    if(totalRow)
    {
        totalPoints+=100*totalRow*totalRow;
        noOfRemovedRow=totalRow;

    }

    else noOfRemovedRow=0;


    isFilled=false;
    filledRow.clear();
    return totalRow;

}

