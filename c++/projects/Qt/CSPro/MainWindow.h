#ifndef MAIN_WINDOW__H
#define MAIN_WINDOW__H

#include <QMainWindow>

class QAction;
class QToolBar;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;

class AnalysisWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();

protected:

    void closeEvent( QCloseEvent* event );

private slots:

    void newAnalysisWindow();
    void copyAnalysisWindow();
    void reportWindow();
    void about();
    void help();

    void setActiveSubWindow( QWidget *window );
    void updateActions();

private:

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    AnalysisWindow* createAnalysisWindow();
    AnalysisWindow* activeMdiChild();

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* windowMenu;
    QMenu* helpMenu;

    QToolBar* toolBar;

    QAction* newAnalysisAction;
    QAction* copyAnalysisAction;
    QAction* reportAction;
    QAction* aboutAction;
    QAction* helpAction;
    QAction* exitAction;
    QAction* arrangeWindowsAction;

    QMdiArea* mdiArea;
    QSignalMapper *windowMapper;
};


#endif
