#include <string>
#include <iostream>
#include <vector>

#include "boost/shared_ptr.hpp"
#include "boost/bind.hpp"

using namespace std;

class Atom
{
public:
    
    Atom( const string& a ) :
        _name( a ){}

    ~Atom() {
        cout << "Atom::~Atom: " << _name << endl;
    }

    string name() const { return _name; }

private:

    string _name;
};

class AtomManager
{
public:

    void free( Atom* atom ) {
        cout << "AtomManager::free freeing Atom: " << atom->name() << endl;
        delete atom;
    }

};

class RunnableAtom
{
public:
    
    RunnableAtom( const string& a ) :
        _name( a ),
        _terminated( false )
    {
        cout << "created RunnableAtom: " << _name << endl;
    }

    ~RunnableAtom() {
        cout << "RunnableAtom::~RunnableAtom: " << _name << endl;
    }

    string name() const { return _name; }

    void terminate() const { cout << _name << ".terminate" << endl; _terminated = true; }
    bool isTerminated() const { return _terminated; }

    bool update() const { cout << _name << ".update" << endl; return isTerminated(); }

private:

    string _name;
    mutable bool _terminated;
};


class RunnableManager
{
public:

    typedef vector< RunnableAtom* >::iterator iterator;

    ~RunnableManager()
    {
        iterator ix = _atoms.begin();
        while( ix != _atoms.end() ) {
            delete (*ix);
            ix = _atoms.erase( ix );
        }
    }
    
    void run() {
        iterator ix = _atoms.begin();
        while( ix != _atoms.end() ) {
            if( (*ix)->update() ) {
                delete (*ix);
                ix = _atoms.erase( ix );
            } else {
                ix++;
            }
        }
    }

    void add( RunnableAtom* atom ) {
        _atoms.push_back( atom );
    }

private:
    
    vector< RunnableAtom* > _atoms;
};


int main( int argc, char** argv )
{
    {
        boost::shared_ptr< Atom > atom( new Atom( "thing1" ), boost::bind( &AtomManager::free, AtomManager(), _1  ) );
        cout << "created Atom: " << atom->name() << endl;

        cout << "going out of scope..." << endl;
    }


    RunnableManager manager;

    {
        boost::shared_ptr< RunnableAtom > atom( new RunnableAtom( "New RunnableAtom 1" ),
                                                boost::bind( &RunnableAtom::terminate, _1 ) );
        manager.add( atom.get() );
        manager.run();

        boost::shared_ptr< RunnableAtom > atom2( new RunnableAtom( "New RunnableAtom 2" ),
                                                 std::mem_fun( &RunnableAtom::terminate ) );

        manager.add( atom2.get() );
        manager.run();
    }

    manager.run();
    cout << "going out of scope..." << endl;

    return 0;
}


