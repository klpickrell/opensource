#include <iostream>
#include <map>

using namespace std;

class Handler {

public:

  Handler() {
    TotalHandlers++;
    _id = TotalHandlers;
  }

public:

  void handler1() const { cout << "Handler[" << _id << "]::handler1 handling request" << endl; }
  void handler2() const { cout << "Handler[" << _id << "]::handler2 handling request" << endl; }
  void handler3() const { cout << "Handler[" << _id << "]::handler3 handling request" << endl; }

private:

  static int TotalHandlers;

  int _id;
};

int Handler::TotalHandlers = 0;
typedef void (Handler::*HandlerFunction)() const;

class Command {

public:
  
  ~Command() {
    map< const Handler*, HandlerFunction >::iterator ix = _handlers_map.begin();
    for( ix; ix != _handlers_map.end(); ix++ ) {
      delete ix->first;
    }
  }

public:

  void execute() {
    map< const Handler*, HandlerFunction >::iterator ix = _handlers_map.begin();
    for( ix; ix != _handlers_map.end(); ix++ ) {
      (ix->first->*(ix->second))();
    }
  }

public:

  void add( const Handler* handler, HandlerFunction handlerfunc )
  {
    if( handler && handlerfunc ) {
      _handlers_map.insert( pair< const Handler*, HandlerFunction >( handler, handlerfunc ) );
    }
  }

private:

  map< const Handler*, HandlerFunction > _handlers_map;
};

int main( int argc, char** argv )
{
  
  Command com;

  com.add( new Handler(), &Handler::handler1 );
  com.add( new Handler(), &Handler::handler3 );
  com.add( new Handler(), &Handler::handler2 );
  com.add( new Handler(), &Handler::handler1 );
  com.add( new Handler(), &Handler::handler2 );
  com.add( new Handler(), &Handler::handler2 );

  com.execute();
  
  return 0;
}


