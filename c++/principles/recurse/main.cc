#include <iostream>

using namespace std;

struct node {
  int data;
  node* link;
};

typedef struct node* list;

int SumUp( list& L ) {
  if( !L->link ) {
    return L->data;
  } else {
    return L->data + SumUp( L->link );
  }
}

int main( int argc, char** argv )
{
  list l = new node;
  l->data = 1;
  l->link = 0;

  list iter = l;

  int arr[] = {1, 2, 33 };
  int arrsize = sizeof( arr ) / sizeof( arr[0] );

  for( int i = 0; i < arrsize; i++ ) {

    iter->link = new node;
    iter = iter->link;
    iter->link = 0;
    iter->data = arr[i];
  }

  cout << "iter contains: ";
  iter = l;
  while( iter ) {
    cout << iter->data << " ";
    iter = iter->link;
  }
  cout << endl;

  int sum = SumUp( l );

  cout << "sum is " << sum << endl;

  iter = l;
  while( iter ) {
    list temp = iter;
    iter = iter->link;

    delete( temp );
  }
  
  return 0;
}

