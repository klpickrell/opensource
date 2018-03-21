#include <list>
#include <iostream>
#include "boost/shared_ptr.hpp"

using namespace std;
using namespace boost;

class ModuleTask
{
public:
    ModuleTask() { cout << "ModuleTask::ModuleTask" << endl; }
    virtual void doit() const { cout << "ModuleTask::doit" << endl; }
};

class DerivedTask : public ModuleTask
{
public:
    DerivedTask() : ModuleTask() { cout << "DerivedTask::DerivedTask" << endl; }
    void doit() const { cout << "DerivedTask::doit" << endl; }
};

void add( shared_ptr< ModuleTask > task ) {
    cout << "Adding shared ptr< ModuleTask >... doit returns: ";
    task->doit();
    list< shared_ptr< ModuleTask > > l;
    l.push_back( task );
}

void add( shared_ptr< DerivedTask > task ) {
    cout << "Adding shared ptr< DerivedTask >... doit returns: ";
    task->doit();
    list< shared_ptr< ModuleTask > > l;
    l.push_back( task );
}


int main( int argc, char** argv )
{
    shared_ptr< DerivedTask > dp( new DerivedTask );
    shared_ptr< ModuleTask > dp2( new DerivedTask );
    add( dp );
    add( dp2 );
    
    return 0;
}


