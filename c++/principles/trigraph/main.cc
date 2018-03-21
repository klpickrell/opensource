??=include <iostream>

using namespace std;

int main( int argc, char** argv )
??<
    int a??( ??) = ??< 1, 2, 3 ??>;
    for( int i = 0; i < sizeof(a)/sizeof(a??(0??)); i++ ) ??<
        cout << " a[" << i << "]=" << a??(i??);
    ??>
    cout << endl;

    if( ??-(sizeof(a)/sizeof(a??(0??)))) ??<
    ??> else ??<
        cout << "a has no elements" << endl;
    ??>

    // the line below will never execute ??/
    cout << "neither will the next one" << endl; \
    cout << "that's right" << endl

    return 0;
??>


