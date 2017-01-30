#include <iostream>
#include "myDerivedCLass.h"
#include "AI_player.h"
#include "userInterface.h"
#include "visualization.h"

using namespace std;

int main ()
{
    int a;
    cout<<"Choose 1 for AI 2 for User mood:";
    cin>>a;

    if (a==1)
    {
        myIBoard myGameBoard;
        visualization show(&myGameBoard);

        AI_player playGame;

        playGame.properPosition (&myGameBoard);
       // playGame.boardHeight();
       // playGame.Play(&myGameBoard);

     }

    else if (a==2)

    {
        myIBoard myGameBoard;
        visualization show(&myGameBoard);
        userInterface playGame(&myGameBoard);
        playGame.Play(&myGameBoard,&show);


    }
}
