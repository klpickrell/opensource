#include <vector>
#include <iostream>
#include <algorithm>

#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
#include "Timer.h"

using namespace std;
using namespace boost::assign;

int main( int argc, char** argv )
{
    int trials = 1000000;
    vector<char> frame1;
    vector<char> frame2;
    vector<char> frame3;

    frame1 += 'A',repeat( trials, 'A' );

    cout << "frame2 size is: " << frame2.size() << endl;
    cout << "Reserve " << frame1.size() << " and std::copy using back_inserter: ";
    Timer t1;
    frame2.reserve( frame1.size() );
    std::copy( frame1.begin(), frame1.end(),
               back_inserter( frame2 ) );

    cout << t1.elapsed() << "s" << endl;
    cout << "frame2 size is: " << frame2.size() << endl;

    cout << "frame3 size is: " << frame3.size() << endl;
    cout << "Reserve " << frame1.size() << " and memcpy: ";
    Timer t2;
    frame3.reserve( frame1.size() );
    frame3.resize( frame1.size() );
    memcpy( &frame3[0], &frame1[0], frame3.size() );
    
    cout << t2.elapsed() << "s" << endl;

    cout << "frame3 size is: " << frame3.size() << endl;


    cout << "frame1.capacity is: " << frame1.capacity() << endl;
    cout << "frame1.size is: " << frame1.size() << endl;
    cout << "resizing by 10..." << endl;
    frame1.resize( frame1.size() + 10 );
    cout << "frame1.capacity is: " << frame1.capacity() << endl;
    cout << "frame1.size is: " << frame1.size() << endl;
    cout << "clearing with clear..." << endl;
    frame1.clear();
    cout << "frame1.capacity is: " << frame1.capacity() << endl;
    cout << "frame1.size is: " << frame1.size() << endl;

    return 0;
}


