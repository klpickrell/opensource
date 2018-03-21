#include <qapplication.h>
#include <qslider.h>
#include <qlcdnumber.h>

int main( int argc, char** argv ) 
{
    QApplication myapp( argc, argv );
    
    QWidget* mywidget = new QWidget();
    mywidget->setGeometry( 400, 300, 170, 110 );

    QSlider* myslider = new QSlider( 0, 9, 1, 1, QSlider::Horizontal, mywidget );
    myslider->setGeometry( 10, 10, 150, 30 );

    QLCDNumber* mylcdnum = new QLCDNumber( 1,
                                           mywidget );

    mylcdnum->setGeometry( 60, 50, 50, 50 );
    
    mylcdnum->display( 1 );

    QObject::connect( myslider, SIGNAL( sliderMoved( int ) ),
                      mylcdnum, SLOT( display( int ) ) );

    myapp.setMainWidget( mywidget );
    mywidget->show();

    return myapp.exec();
}


