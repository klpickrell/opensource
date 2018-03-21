#include <iostream>

using namespace std;

void doit()
{
  cout << "doing it!" << endl;
  return void(1);
}

int main( int argc, char** argv )
{
  doit();
  return 0;
}


