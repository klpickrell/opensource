#ifndef MAIN_WINDOW__H
#define MAIN_WINDOW__H

#include <qmainwindow.h>
#include <qaction.h>
#include <qmap.h>
#include "newgamedialog.h"


class MainFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();


protected:

    void closeEvent(QCloseEvent*);

private slots:

    void fileNewSlot();
    void analyzeButtonClickedSlot();
    void toggleNumbersButtonClickedSlot();

    void workingSlot(bool);

    void warning(const QString& text);


private:

    void make_menu();
    void make_mainframe();

    void information(const QString& caption, const QString& text);

    void initialize_board();

private:
    QMenu* viewMenu;
    QAction* gameNew;
    NewGameDialog* newGameDialog;

    MainFrame* _mainframe;
    bool _showNotation;
};

#endif

