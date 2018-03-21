int main( int argc, char** argv )
{
  switch( argc ) {
  case 1:
    return 1;
  case 2:
    return 2;
  case 3:
    {
      int* mem = 0;
      for( int i = 0; i < 10000; i++ ) {
	mem[i] = i;
      }
      return 3;
    } break;
  default:
    break;
  }
  return 0;
}


