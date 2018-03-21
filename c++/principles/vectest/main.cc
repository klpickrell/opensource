#include <map>
#include <vector>
#include <iostream>

using namespace std;

class babyclass
{

public:
  virtual void dosomething() const { cout << "something" << endl; }

  virtual ~babyclass() {}


private:

};

class mamaclass : public babyclass
{

};

int main( int argc, char** argv )
{
  map< string, vector< babyclass* > > _handlers;

  _handlers[ "^status" ].push_back( new mamaclass() );
  _handlers[ "^status" ].push_back( new mamaclass() );
  _handlers[ "^status" ].push_back( new mamaclass() );
  _handlers[ "^start" ].push_back( new mamaclass() );
  _handlers[ "^start" ].push_back( new mamaclass() );
  _handlers[ "^finish" ].push_back( new mamaclass() );
  _handlers[ "^other" ].push_back( new mamaclass() );
  _handlers[ "^other" ].push_back( new mamaclass() );
  _handlers[ "^other" ].push_back( new mamaclass() );
  _handlers[ "^none" ].push_back( new mamaclass() );

  typedef map< string, vector< babyclass* > >::const_iterator handlers_const_iterator;
  typedef map< string, vector< babyclass* > >::iterator handlers_iterator;

  for( handlers_const_iterator ix = _handlers.begin();
       ix != _handlers.end();
       ix++ ) {

    cout << "\"" << ix->first << "\"==>" << endl;
    for( vector< babyclass* >::const_iterator vh = ix->second.begin();
         vh != ix->second.end(); 
         vh++ ) {
      cout << "\t" << (*vh) << endl;
    }
  }          


  cout << "removing handlers" << endl;

  for( handlers_iterator ix = _handlers.begin();
       ix != _handlers.end(); ) {

    vector< babyclass* >& bbcr = ix->second;
    //    for( vector< babyclass* >::iterator vh = ix->second.begin();
    //         vh != ix->second.end(); ) {

    for( vector< babyclass* >::iterator vh = bbcr.begin();
         vh != bbcr.end(); ) {
                
      babyclass* h = (*vh);
      cout << "Attempting to dynamic_cast " << h << endl;
      mamaclass* snlh = dynamic_cast< mamaclass* >( h );
      if( snlh ) {
        cout << "removing \"" << ix->first << "\" handled by " << snlh << endl;
        delete( snlh );

        cout << "erasing " << (*vh) << endl;
        vh = bbcr.erase( vh );
      } else {
        vh++;
      }
    }

    if( bbcr.empty() ) {
      _handlers.erase( ix++ );
    } else {
      ix++;
    }

    cout << "map now looks like:" << endl;
    for( handlers_const_iterator ix = _handlers.begin();
         ix != _handlers.end();
         ix++ ) {

      cout << "\"" << ix->first << "\"==>" << endl;
      for( vector< babyclass* >::const_iterator vh = ix->second.begin();
           vh != ix->second.end(); 
           vh++ ) {
        cout << "\t" << (*vh) << endl;
      }
    }
  }

  cout << "done, output follows" << endl;



  return 0;
}

