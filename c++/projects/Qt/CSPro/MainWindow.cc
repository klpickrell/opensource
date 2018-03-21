#include <QtGui>
#include "MainWindow.h"
#include "AnalysisWindow.h"
#include "HelpWindow.h"
#include "ReportWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle( tr( "CacheSimulation Pro" ) );
    resize( 800, 600 );

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),
            this, SLOT(updateActions()));
    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget *)),
            this, SLOT(setActiveSubWindow(QWidget *)));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    updateActions();
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    event->accept();
}

void MainWindow::updateActions()
{
    bool mdi = (activeMdiChild() != 0);
    copyAnalysisAction->setEnabled( mdi );
}

void MainWindow::reportWindow()
{
    ReportWindow* reportwin = new ReportWindow( this );
    reportwin->show();    
}

void MainWindow::newAnalysisWindow()
{
    AnalysisWindow* child = createAnalysisWindow();
    child->show();
}

void MainWindow::copyAnalysisWindow()
{
    if( activeMdiChild() ) {
        AnalysisWindow* orig = activeMdiChild();
        AnalysisWindow* child = createAnalysisWindow();
        child->copyConfig( *orig );
        child->show();
    }
}

AnalysisWindow* MainWindow::createAnalysisWindow()
{
    AnalysisWindow* analysis = new AnalysisWindow( this );
    mdiArea->addSubWindow( analysis );
    analysis->setWindowTitle( "New Analysis" );
    //    analysis->resize( 400, 300 );

    return analysis;
}

void MainWindow::createActions()
{
    newAnalysisAction = new QAction( QIcon( ":/images/new.png" ),
                                     tr( "&New Analysis" ),
                                     this );
    newAnalysisAction->setShortcuts( QKeySequence::New );
    newAnalysisAction->setStatusTip( "Launch a new analysis window" );
    connect( newAnalysisAction, SIGNAL( triggered() ),
             this, SLOT( newAnalysisWindow() ) );

    copyAnalysisAction = new QAction( QIcon( ":/images/copy.png" ),
                                      tr( "&Copy Analysis" ),
                                      this );
    copyAnalysisAction->setShortcuts( QKeySequence::Copy );
    copyAnalysisAction->setStatusTip( "Copy selected analysis window" );
    connect( copyAnalysisAction, SIGNAL( triggered() ), 
             this, SLOT( copyAnalysisWindow() ) );

    reportAction = new QAction( QIcon( ":/images/report.png" ),
                                tr( "&Generate Report" ),
                                this );
    reportAction->setStatusTip( "Generate Analysis Report" );
    connect( reportAction, SIGNAL( triggered() ), 
             this, SLOT( reportWindow() ) );

    helpAction = new QAction( QIcon( ":/images/help.png" ),
                              tr( "Help" ),
                              this );
    helpAction->setStatusTip( "Open Help System" );
    connect( helpAction, SIGNAL( triggered() ),
             this, SLOT( help() ) );

    aboutAction = new QAction( tr( "About" ),
                               this );
    aboutAction->setStatusTip( "About CacheSimulation Pro" );
    connect( aboutAction, SIGNAL( triggered() ),
             this, SLOT( about() ) );


    exitAction = new QAction( QIcon( ":/images/exit.png" ),
                              tr( "E&xit" ),
                              this );
    exitAction->setStatusTip( "Exit the application" );
    connect( exitAction, SIGNAL( triggered() ),
             qApp, SLOT( closeAllWindows() ) );

    arrangeWindowsAction = new QAction( QIcon( ":/images/tile.png" ),
                                        tr( "&Tile Windows" ), this );
    arrangeWindowsAction->setStatusTip( tr( "Tiles windows in workspace" ) );
    connect( arrangeWindowsAction, SIGNAL( triggered() ),
             mdiArea, SLOT( tileSubWindows() ) );
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr("&File") );
    fileMenu->addAction( newAnalysisAction );
    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );

    editMenu = menuBar()->addMenu( tr("&Edit") );
    editMenu->addAction( copyAnalysisAction );
    editMenu->addAction( reportAction );

    windowMenu = menuBar()->addMenu( tr("&Window") );
    windowMenu->addAction( arrangeWindowsAction );
    windowMenu->addSeparator();

    helpMenu = menuBar()->addMenu( tr( "Help" ) );
    helpMenu->addAction( helpAction );
    helpMenu->addSeparator();
    helpMenu->addAction( aboutAction );
}

void MainWindow::createToolBars()
{
    toolBar = addToolBar( tr("File") );
    toolBar->addAction( newAnalysisAction );
    toolBar->addAction( copyAnalysisAction );
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage( tr("Ready") );
}

void MainWindow::about()
{
    QMessageBox::about( this, tr( "About CacheSimulation Pro" ),
                        tr( "<i>CacheSimulation Pro</i><br>"
                            "Version 0.1<br>"
                            "Copyright (C) 2009" ) );
}

void MainWindow::help()
{
    HelpWindow* helpwin = new HelpWindow( this );
    helpwin->setAttribute( Qt::WA_QuitOnClose );
    helpwin->show();
}

AnalysisWindow* MainWindow::activeMdiChild()
{
    QMdiSubWindow* window = mdiArea->activeSubWindow();
    if( window ) {
        return qobject_cast<AnalysisWindow*>( window );
    }

    return 0;
}
void MainWindow::setActiveSubWindow( QWidget *window )
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow( qobject_cast<QMdiSubWindow *>(window) );
}
