#include <iostream>
#include <sstream>
#include <string>
#include <netdb.h>
#include <errno.h>

using namespace std;

int main( int argc, char** argv )
{


  /*
  hostent* h = gethostbyname( "kris-p" );
  ostringstream os;
  os << "gethostbyname returned:" << endl
     << "official name (h_name)=" << h->h_name << endl;
  int i = 0;
  while( h->h_aliases[i] ) {
    os << "alias (h_aliases)=" << h->h_aliases[i] << endl;
    i++;
  }
  os << "address type (h_addrtype)=" << h->h_addrtype << endl;
  os << "address length (h_length)=" << h->h_length << endl;
  i = 0;
  while( h->h_aliases[i] ) {
    os << "address list (h_addr_list)=" << h->h_addr_list[i] << endl;
    i++;
  }

  cout << os.str();

  char name[256];
  errno = 0;
  if( gethostname( name, sizeof( name ) ) ) {
    cout << "oops, gethostname failed with error: " << strerror( errno ) << endl;
  } else {
    cout << "gethostname returned: '" << name << "'" << endl;
  }
  */
    
  /*
  ostringstream os;
  for( int i = 0; ; i++) {
    os << "executing run " << i+1 << endl;
    cout << os.str();
  }
  cout << "done" << endl;
  return 0;

  string blah = "bind status";
  string inp;
  while( getline( cin, inp ) ) {
    cout << endl;
    string::size_type t = blah.find( inp.c_str(), 0, inp.length() );
    if( t == string::npos ) {
      cout << inp << " not found in " << blah << endl;
    } else {
      ostringstream os;
      os << inp << " found at position " << t << endl;
      cout << os.str();
    }
  }
  */
  return 0;
}
