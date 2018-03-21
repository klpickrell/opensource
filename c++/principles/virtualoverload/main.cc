#include <iostream>

using namespace std;

class Task
{
public:
    virtual bool update() const { cout << "MyTask::update" << endl; return true; }
};

class MyTask : public Task
{
public:
    bool update() const { cout << "MyTask::update" << endl; return true; }
};

class State
{
public:
    virtual bool update( Task* t ) = 0;// { cout << "State::update" << endl; return t->update(); }
};

class DerivedState : public State
{
public:
    bool update( MyTask* t ) { cout << "DerivedState::update" << endl; return t->update(); }
};


int main( int argc, char** argv )
{

    Task* t = new Task;
    MyTask* myt = new MyTask;

    State* s = new DerivedState;

    s->update( myt );


    return 0;
}


