#ifndef INTERFACES_H_
#define INTERFACES_H_

// Enum for the different block types .
enum BlockType_E
{
    I_Block_e , L_Block_e , T_Block_e , J_Block_e ,
    S_Block_e , O_Block_e , Z_Block_e
};

// Enum for the movement of the block .
enum Movement_E
{
    MoveLeft_e , MoveRight_e ,
    RotateClockwise_e , RotateCounterClockwise_e ,
    Release_e
};

class IBoard
{
public :
    IBoard() {} ;
    virtual ~IBoard() {} ;
	
    // Initializes the board with a random current and next block .
    virtual void InitBoard() = 0 ;
	
    // Returns the field at the given position .
    // A value of 0 means empty , all other values represent
    // occupied by an element of a block .
    virtual unsigned int GetField( unsigned int PosX , unsigned int PosY ) const = 0 ;
	
    // Moves the current block .
    virtual void Move ( Movement_E Movement ) = 0 ;
	
    // Returns true , if the game is finished and false otherwise .
    virtual bool IsFinished() const = 0 ;
	
    // Returns the next block type .
    virtual BlockType_E GetNextBlockType() const = 0 ;
	
    // Returns the current amount of points .
    virtual unsigned int GetPoints() const = 0 ;
	
    // Returns the current amount of removed rows .
    virtual unsigned int GetRemovedRows() const = 0 ;
};

class IPlayer
{
public :
    IPlayer () {} ;
    virtual ~ IPlayer () {} ;
	
    // Plays the given board by moving the block .
    virtual void Play ( IBoard * pBoard ) = 0 ;
};

#endif /*INTERFACES_H_*/
