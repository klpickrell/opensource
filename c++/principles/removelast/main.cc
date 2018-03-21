#include <iostream>

using namespace std;

struct node {
  int data;
  node* link;
};

typedef struct node* list;

void RemoveLast( list& L, int x ) {

  if( !L ) {
    return;
  }

  list lastfound = 0;
  list lastfoundpre = 0;

  if( L->data == x ) {

    if( !L->link ) {
      L = L->link;
      return;
    } else {
      lastfound = L;
    }
  }

  list precursor = L;
  list cursor = L->link;

  while( cursor ) {
    if( cursor->data == x ) {
      lastfoundpre = precursor;
      lastfound = cursor;
    }

    precursor = cursor;
    cursor = cursor->link;
  }

  if( lastfound ) {
    if( lastfoundpre ) {
      lastfoundpre->link = lastfoundpre->link->link;
    } else {
      L = L->link;
    }
  }
}

int main( int argc, char** argv )
{
  list l = new node;
  l->data = 1;
  l->link = 0;

  list iter = l;

  int arr[] = {};
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

  RemoveLast( l, 1 );

  cout << "iter contains: ";
  iter = l;
  while( iter ) {
    cout << iter->data << " ";
    iter = iter->link;
  }
  cout << endl;

  iter = l;
  while( iter ) {
    list temp = iter;
    iter = iter->link;

    delete( temp );
  }
  
  return 0;
}


