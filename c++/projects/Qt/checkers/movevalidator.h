#ifndef CHECKERS_H
#define CHECKERS_H


#include <qstring.h>


// do not change - hard coded
#define NONE_ENTRY   0
#define MAN1   1
#define KING1  2
#define FREE   3
#define KING2  4
#define MAN2   5
#define FULL   6

#define UL -6
#define UR -5
#define DL  5
#define DR  6


class MoveValidator
{
public:
    MoveValidator();
    virtual ~MoveValidator() {}

    bool setup(int setupboard[]);
    virtual bool go1(int from, int to) { return false; }

    void go2();

    void setSkill(int i) { levelmax=i; };
    int skill() const { return levelmax; }

    int item(int i) const { return board[internal(i)]; }
    void setItem(int i, int item) { board[internal(i)] = item; }

    // string representation of the game board.
    // set rotate to switch player sides.
    QString toString(bool rotate) const;
    bool fromString(const QString&);

    // checks for a capture/move for particular stone in external
    // representation. human player only.
    bool canCapture1(int i) { return checkCapture1(internal(i)); }
    bool canMove1(int i) { return checkMove1(internal(i)); }

    bool checkMove1() const;
    bool checkMove2() const;

    virtual bool checkCapture1() const { return false; }
    virtual bool checkCapture2() const { return false; }

protected:
    bool checkMove1(int) const;
    virtual bool checkCapture1(int) const { return false; }

    int level;        // Current level
    int levelmax;     // Maximum level

    int  turn();
    void turn(int&, bool capture=false);

    int to;
    int board[54];
    int bestboard[54];
    int bestcounter;

    virtual void kingMove2(int,int &) {}

    virtual bool manCapture2(int,int &) { return false; }
    virtual bool kingCapture2(int,int,int &) { return false; }

    virtual bool manCapture1(int,int,bool &) { return false; }
    virtual bool kingCapture1(int,int,bool &) { return false; }

    int internal(int) const;	// Return internal board position
};


#endif
