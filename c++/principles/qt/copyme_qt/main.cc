#include <qapplication.h>
#include <qlabel.h>

int main( int argc, char* argv[] )
{
  QApplication myapp( argc, argv );

  QLabel* mylabel = new QLabel( "Hello, world", 0 );
  mylabel->resize( 120, 30 );

  myapp.setMainWidget( mylabel );
  mylabel->show();
  return myapp.exec();
}


