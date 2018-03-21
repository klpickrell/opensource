(1)  #include <stdio.h>

(2)  int gcd(int #u, double v );
(3)  { if( v = 0 ) return 0;
(4)    else return gcd( v, u# % v );
(5)  }


(6)  main()
(7)  { int x, y;
(8)    printf( "Input two integers: " );
(9)    scanf( "%d%d",&x,&y );
(10)   printf( "The gcd of %d and %d is %d\n",
               x,y,Gcd(x,y));
(11)   return;
(12) }


