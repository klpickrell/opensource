#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include "boost/bind.hpp"

using namespace std;

int main( int argc, char** argv )
{
    //    ifstream file( "default.txt", ios::in );
    //    istream_iterator<string> start( file );
    //    istream_iterator<string> end;
    //    vector<string> lines( start, end );

    ifstream file("default.txt");
    string line;

    vector<string> lines;
    while (std::getline(file, line)) {
        lines.push_back( line );
    }

    cout << "file has " << lines.size() << " lines" << endl;
    for( vector<string>::iterator it = lines.begin();
         it != lines.end();
         ++it ) {
        cout << "LINE: " << *it << endl;
    }
    
    return 0;
}


