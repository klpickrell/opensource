#include "PointerBank.h"

#include <string>
#include <iostream>

using namespace std;

class Animal {

public:
    virtual void doit() = 0;
    virtual string id() const = 0;
};

class MonkeyJob : public Animal
{
public:
  MonkeyJob( const string& id ) {
    _id = id;

    PointerBank< MonkeyJob >::instance()->add( this );
    PointerBank< Animal >::instance()->add( this );
  }

  void doit() {
    cout << "MonkeyJob! _id=" << _id << endl;
  }

  string id() const { return _id; }


private:
  string _id;
};

class DolphinJob : public Animal
{
public:
  DolphinJob( const string& id ) {
    _id = id;

    PointerBank< DolphinJob >::instance()->add( this );
    PointerBank< Animal >::instance()->add( this );
  }

  void doit() {
    cout << "DolphinJob! _id=" << _id << endl;
  }

  string id() const { return _id; }


private:
  string _id;

};


int main( int argc, char** argv )
{
    new MonkeyJob( "monkey1" );
    new MonkeyJob( "monkey2" );
    new MonkeyJob( "monkey3" );

    list< Animal* > animals = PointerBank< Animal >::instance()->getall();
    cout << "list< Animal* > size=" << animals.size() << endl;

    Animal* myani = PointerBank< Animal >::instance()->getfirst( "monkey1" );
    if( myani ) {
        cout << "Got a Monkey as Animal" << endl;
        myani->doit();
    } else {
        cout << "Didn't get a Monkey as Animal" << endl;
    }
  
  
    return 0;
}


