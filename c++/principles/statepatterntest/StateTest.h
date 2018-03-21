#ifndef STATE_TEST_H
#define STATE_TEST_H

#include "boost/shared_ptr.hpp"
#include <string>

using namespace std;

class Context;
class State {
public:
    State( Context* context ) :
        _context( context )
    {}

    virtual ~State() {}
    
    virtual void printName() {
        cout << "printName called from State!" << endl;
    }

    Context* context() { return _context; }
    const Context* context() const { return _context; }

private:
    Context* _context;
};


class Context {
public:
    
    Context();

    boost::shared_ptr< State > getState() {
        cout << "non const getState" << endl;
        return m_state;
    }

    boost::shared_ptr< const State > getState() const {
        cout << "const getState" << endl;
        return m_state;
    }

    void setState( State* state ) {
        cout << "Context::setState" << endl;
        m_state = boost::shared_ptr< State >( state );
    }

    string name() const { return string( "I'm the context" ); }

    void printName( bool wrong ) { 

        if( wrong ) {
            // incorrect: causes the shared_ptr to be deleted, printName may set state invalidating m_state
            m_state->printName();
        } else {
            // correct: generates a temporary, keeps the shared_ptr alive long enough
            getState()->printName();
        }
    }

private:

    boost::shared_ptr< State > m_state;
};

class RunState : public State
{
public:
    RunState( Context* context ) :
        State( context )
    {
        cout << "RunState::RunState" << endl;
    }

    ~RunState() {
        cout << "RunState::~RunState" << endl;        
    }

    void printName();
};

class InitialState : public State
{
public:
    InitialState( Context* context ) :
        State( context )
    {
        cout << "InitialState::InitialState" << endl;
    }

    ~InitialState() {
        cout << "InitialState::~InitialState" << endl;
    }

    void printName() {
        cout << "InitialState::printName on " << context()->name() << endl;
        context()->setState( new RunState( context() ) );
        cout << "InitialState::printName exit" << endl;
    }
};


#endif
