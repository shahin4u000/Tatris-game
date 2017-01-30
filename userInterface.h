#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "myDerivedCLass.h"
#include "visualization.h"


class userInterface : public myIBoard
{
public:
    userInterface(IBoard *obj);
    void Play (IBoard *obj, visualization *showBoard) ;
};

#endif // USERINTERFACE_H
