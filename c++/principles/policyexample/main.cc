#include <iostream>
#include <stdlib.h>

using namespace std;

class Widget
{
public:
  Widget() { cout << "Widget.Widget" << endl; }
  ~Widget() { cout << "Widget.~Widget" << endl; }
  void doit() { cout << "Widget.doit" << endl; }

};

template< class T > 
class NewCreator
{
public:
  T* create() {     
    cout << "NewCreator.create" << endl;
    return new T(); 
  }
};

template<>
class NewCreator< int >
{
public:
  int* create() {     
    cout << "NewCreator<int>.create" << endl;
    return new int(); 
  }
};

template< class T >
class RepositoryCreator
{
public:
  T* create() {
    cout << "RepositoryCreator.create" << endl;
    char* repos = new char[ sizeof( T ) ];
    return new( repos ) T();
  }
};

template< class T >
class WidgetManager : public T
{
public:
  Widget* createWidget() {
    return this->create();
  }
};


int main( int argc, char** argv )
{

  WidgetManager< NewCreator< Widget > > ncwidget;
  WidgetManager< RepositoryCreator< Widget > > mcwidget;
  NewCreator< int > nc;
  Widget* wn = ncwidget.createWidget();
  Widget* wm = mcwidget.createWidget();
  int* i = nc.create();

  wn->doit();
  wm->doit();

  cout << "freeing widget" << endl;
  delete wm;
  cout << "deleting widget" << endl;
  delete wn;

  return 0;
}


