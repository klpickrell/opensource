#include <iostream>

using namespace std;

class Widget
{
public:
  Widget() { cout << "Widget.Widget" << endl; }
  ~Widget() { cout << "Widget.~Widget" << endl; }
  void doit() { cout << "Widget.doit" << endl; }

};

int main( int argc, char** argv )
{

  cout << "mallocing repos" << endl;
  char* area = new char[ sizeof( Widget ) ];

  cout << "creating Widget with placement new" << endl;
  Widget* p = new( area ) Widget();

  cout << "deleting Widget with normal delete" << endl;
  p->~Widget();
  delete[] area;

  cout << "creating Widget (2) with placement new" << endl;
  
  p = new( area ) Widget();

  cout << "deleting Widget (2) with normal delete" << endl;
  delete p;

  return 0;
}


