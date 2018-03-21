#include <iostream>
#include <cstdarg>
#include <sstream>
#include "slog_stream.h"

using namespace std;

void printit( char* buf, size_t size, char* fmt, ... )
{
    va_list vl;
    va_start(vl,fmt);
    int ret = vsnprintf( buf, size, fmt, vl );
    cout << "vsnprintf returned: " << ret << endl;
}

int main( int argc, char** argv )
{
    slog_info << "howdy\n";

    slog_debug << "howdy bro," << " not done yet" << endl;

    slog_debug << "howdy bro," << string(0) << endl;

    slog_debug << "howdy bro," << " still not done yet" << endl;

    slog_info << "further howdies\n";

    return 0;
}
