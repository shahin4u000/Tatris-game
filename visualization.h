#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#include <myDerivedCLass.h>


class visualization
{
public:
    myIBoard *obj;
    visualization(myIBoard *object);
    void display();
};

#endif // VISUALIZATION_H
