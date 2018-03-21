#include <QApplication>
#include <QPlastiqueStyle>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    //    app.setStyle(new QPlastiqueStyle);

    MainWindow* win = new MainWindow();
    win->show();

    int exit = app.exec();

    delete win;

    return exit;
}


