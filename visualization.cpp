#include "visualization.h"

visualization::visualization(myIBoard *object):obj(object)
{


}

void visualization::display()
{
    obj->clear_screen();
    for(int i=0;i<17;i++)
    {
        for (int j=0;j<22;j++)
        {
            switch (obj->gameField[i][j]) {
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
                cout<<obj->GetPoints();
                break;
            case 8:
                cout<<"Removed";
                break;
            case 9:
                cout<<" Rows:";
                break;
            case 10:
                cout<<obj->GetPoints();

            }
            if(j==21) cout<<endl;

        }


       }
    cout<<"Move Left (a/A)                 Move Right(d/D)\n";
    cout<<"Rotate counter clockwise(k/K)   Rotate Clock wise(l/L)\n";
    cout<<"Release (x/X)\n";

}
