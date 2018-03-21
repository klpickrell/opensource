#include <iostream>
#include <stdlib.h>

using namespace std;

struct Cow {
  int stomach[4];
};
struct Vulture {
  double stomach;
};

union Animal {
  Cow cow;
  Vulture vulture;
};


int main( int argc, char** argv )
{
  Animal animal;
  animal.cow.stomach[0] = 0;
  animal.cow.stomach[1] = 1;
  animal.cow.stomach[2] = 2;
  animal.cow.stomach[3] = 3;
  cout << "animal.cow.stomach[0]: " << animal.cow.stomach[0] << endl 
       << "animal.cow.stomach[1]: " << animal.cow.stomach[1] << endl 
       << "animal.cow.stomach[2]: " << animal.cow.stomach[2] << endl 
       << "animal.cow.stomach[3]: " << animal.cow.stomach[3] << endl;

  cout << "animal.vulture.stomach: " << animal.vulture.stomach << endl;
  cout << "changing to 3.14159..." << endl;
  animal.vulture.stomach = 3.14159;
  cout << "animal.vulture.stomach: " << animal.vulture.stomach << endl;

  cout << "dynamic memory test..." << endl;
  Animal* animal2 = (Animal*)malloc( sizeof( Animal ) );
  animal2->cow.stomach[0] = 0;
  animal2->cow.stomach[1] = 1;
  animal2->cow.stomach[2] = 2;
  animal2->cow.stomach[3] = 3;
  cout << "animal2->cow.stomach[0]: " << animal2->cow.stomach[0] << endl 
       << "animal2->cow.stomach[1]: " << animal2->cow.stomach[1] << endl 
       << "animal2->cow.stomach[2]: " << animal2->cow.stomach[2] << endl 
       << "animal2->cow.stomach[3]: " << animal2->cow.stomach[3] << endl;

  cout << "animal2->vulture.stomach: " << animal2->vulture.stomach << endl;
  cout << "changing to 3.14159..." << endl;
  animal2->vulture.stomach = 3.14159;
  cout << "animal2->vulture.stomach: " << animal2->vulture.stomach << endl;
  free( animal2 );
  return 0;
}


