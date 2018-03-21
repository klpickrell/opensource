#include <QApplication>
#include <QSplashScreen>
#include <QTime>

#include "MainWindow.h"

int main( int argc, char** argv )
{
    Q_INIT_RESOURCE( CSPro );

    QApplication app( argc, argv );
    QPixmap pixmap( ":/images/splash.png" );
    QSplashScreen splash( pixmap );
    splash.show();
    app.processEvents();
    splash.showMessage( QSplashScreen::tr( "Initializing..." ), Qt::AlignLeft | Qt::AlignBottom );

    QTime time;
    time.start();
    while( time.elapsed() < 1e3 ) {
        app.processEvents();
    }
    
    MainWindow mainWindow;
    mainWindow.show();
    splash.finish( &mainWindow );
    return app.exec();
}
