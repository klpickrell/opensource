#include <map>
#include <stdexcept>
#include <iostream>

using namespace std;

int mode( int dataset[], int N )
{
  if( N <= 0 ) {
    throw out_of_range( "Array index invalid" );
  }

  typedef map< int, int > mode_map;
  typedef map< int, int >::iterator mode_map_iter;

  mode_map mymap;

  for( int i = 0; i < N; i++ ) {
    mode_map_iter iter = mymap.find( dataset[i] );
    if( iter != mymap.end() ) {
      mymap[ dataset[i] ]++;
    } else {
      mymap[ dataset[i] ] = 1;
    }
  }

  int max_count = 0;
  int maxval;

  for( mode_map_iter iter = mymap.begin();
       iter != mymap.end();
       iter++ ) {
    if( iter->second > max_count ) {
      max_count = iter->second;
      maxval = iter->first;
    }
  }

  return maxval;
}

int main( int argc, char** argv )
{
  
  int myarr[] = { 1, 2, 5, 5, 6, 3, 3, 1, 1, 5, 5, 5 };
  int myarr_size = sizeof( myarr ) / sizeof( myarr[0] );

  cout << "mode of data is " << mode( myarr, myarr_size ) << endl;


  return 0;
}


