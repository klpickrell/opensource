#include <iostream>

using namespace std;


class TestClass1 {
public:

  TestClass1() {
    cout << "Constructed TestClass1" << endl;
  }
};

class TestClass2 {
public:

  TestClass2() {
    cout << "Constructed TestClass2" << endl;
  }
};

class TestClass3 : public TestClass1 {
public:

  TestClass3() {
    cout << "Constructed TestClass3" << endl;
  }
};

int main( int argc, char** argv )
{

  TestClass1 t1;
  TestClass2 t2;
  TestClass3 t3;
  TestClass2* t4 = new TestClass2();

  cout << "typeid( TestClass1 ): " << typeid( TestClass1 ).name() << endl;
  cout << "typeid( TestClass2 ): " << typeid( TestClass2 ).name() << endl;
  cout << "typeid( TestClass3 ): " << typeid( TestClass3 ).name() << endl;

  cout << "typeid( t1 ): " << typeid( t1 ).name() << endl;
  cout << "typeid( t2 ): " << typeid( t2 ).name() << endl;
  cout << "typeid( t3 ): " << typeid( t3 ).name() << endl;
  cout << "typeid( t4 ): " << typeid( t4 ).name() << endl;

  return 0;
}


