#include <string>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
  string teststr = "start session { blah=10 dcs_cmd_id = 20 blah = 30 };";

  int pos = teststr.find( "dcs_cmd_id" );
  if( pos != string::npos ) {

    string whitespace = "\t\n\r ";
    int endpos = teststr.find_first_of( whitespace, pos );
    int endpos2 = teststr.find_first_of( "=", pos );

    cout << teststr << endl;
    cout << "pos=" << pos << ", endpos=" << endpos << endl;

    string stripped;

    if( endpos2 > endpos ) {
      cout << "dealing with space between equals" << endl;
      stripped = teststr.substr( 0, pos );
      int endpos3 = teststr.find_first_not_of( whitespace, endpos2+1 ); // index of next token
      endpos3 = teststr.find_first_of( whitespace, endpos3 );
      stripped += teststr.substr( endpos3 );
    } else {
    
      stripped = teststr.substr( 0, pos );
      stripped += teststr.substr( endpos );
    }

    cout << stripped << endl;

  } else {
    cout << "dcs_cmd_id not found in " << teststr << endl;
  }

  return 0;
}
