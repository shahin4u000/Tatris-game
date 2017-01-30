#include "userInterface.h"

userInterface::userInterface(IBoard *obj)
{
    obj->InitBoard();


}

void userInterface::Play(IBoard *obj, visualization *showBoard)
{
//    for (int i=0;i<17;i++)
//    {
//        for (int j=0;j<22;j++) {

//            cout << obj->gameField[i][j];
//            if (j==21) {cout<<endl;}
//        }
//    }

    showBoard->display();

    while (!obj->IsFinished())
    {
        unsigned char userInput;
        cin>>userInput;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout<<"Wrong Input!!! Choose 1 for AI 2 for User mood:";
            cin>>userInput;

        }

        switch (userInput)
        {
        case 'a':
        case 'A':
            obj->Move(MoveLeft_e);
            showBoard->display();
            break;
        case 'd':
        case 'D':
            obj->Move(MoveRight_e);
             showBoard->display();
            break;
        case 'x':
        case 'X':
            obj->Move(Release_e);
             showBoard->display();

            break;
        case 'k':
        case 'K':
            obj->Move(RotateCounterClockwise_e);
             showBoard->display();
            break;
        case 'l':
        case 'L':
            obj->Move(RotateClockwise_e);
             showBoard->display();
            break;
//        default:
//            while (cin.fail()) {

//            }
//            cin.clear();
//            cin.ignore(1000,'\n');
//            cout<<"Wrong Input!!! Choose 1 for AI 2 for User mood:";
//            cin>>userInput;
//            break;
        }


    }
}
