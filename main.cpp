#include <iostream>
#include "myDerivedCLass.h"
#include "userInterface.h"
#include "visualization.h"

using namespace std;

int main ()
{
        myIBoard myGameBoard;
        visualization show(&myGameBoard);
        userInterface playGame(&myGameBoard);
        playGame.Play(&myGameBoard,&show);
    
}
