#include <iostream>
#include "StateTest.h"

using namespace std;

Context::Context() {
    setState( new InitialState( this ) );
}

void RunState::printName() {
    cout << "RunState::printName on " << context()->name() << endl;
    context()->setState( new InitialState( context() ) );
    cout << "RunState::printName exit" << endl;
}

int main( int argc, char** argv )
{
    cout << "Making Context" << endl;
    Context context;

    cout << "The wrong way:" << endl;
    context.printName( true );
    cout << "The right way:" << endl;    
    context.printName( false );

    return 0;
}


