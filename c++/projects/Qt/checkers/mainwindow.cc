#include <QLayout>
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QFontDialog>
#include <QDebug>
#include <QPushButton>

#include "mainwindow.h"
#include "mainframe.h"

MainWindow::MainWindow()
{
    setWindowTitle( "Kris Pickrell's Checkers" );
    setWindowIcon(QIcon("./icons/biglogo.png"));

    newGameDialog = new NewGameDialog( this );

    make_mainframe();
    make_menu();

    QAction* thinkAction = new QAction( "Analyze Current Position", this );

    connect( thinkAction, 
             SIGNAL(triggered()), 
             this, 
             SLOT( analyzeButtonClickedSlot() ));

    QAction* toggleAction = new QAction( "Toggle Square Numbers", this );

    connect( toggleAction, 
             SIGNAL(triggered()), 
             this, 
             SLOT( toggleNumbersButtonClickedSlot() ));

    QToolBar* tb = addToolBar(tr("&Toolbar"));
    tb->setMovable( false );
    tb->addAction( thinkAction );
    tb->addSeparator();
    tb->addAction( toggleAction );

    initialize_board();
    _mainframe->setNotation( false,
                             false );

    _mainframe->newGame( 5, ( newGameDialog->isRusselAndNorvig() ? 
                              Engine::RUSSELL_AND_NORVIG :
                              Engine::RICH_AND_KNIGHT ) );

    if(layout())
        layout()->setSizeConstraint(QLayout::SetFixedSize);


    _showNotation = false;
}


void MainWindow::make_menu()
{
    gameNew = new QAction(QIcon("./icons/logo.png"), tr("&New"), this);
    gameNew->setShortcut(tr("CTRL+N", "File|New"));
    connect(gameNew, SIGNAL(triggered()), this, SLOT(fileNewSlot()));

    QAction* gameQuit = new QAction(QIcon("./icons/exit.png"), tr("&Quit"),
                                    this);
    gameQuit->setShortcut(tr("CTRL+Q", "File|Quit"));
    connect(gameQuit, SIGNAL(triggered()),
            this, SLOT(close()));

    QMenu* gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(gameNew);
    gameMenu->addAction(gameQuit);

}

void MainWindow::make_mainframe()
{
    _mainframe = new MainFrame(this);

    connect(_mainframe, SIGNAL(working(bool)),
            this, SLOT(workingSlot(bool)));

    setCentralWidget( _mainframe );
}


void MainWindow::warning(const QString& text)
{
    QMessageBox::warning(this, tr("Error")+" - Checkers", text);
}


void MainWindow::information(const QString& caption, const QString& text)
{
    QDialog* dlg = new QDialog(this);
    dlg->setModal(true);
    dlg->setWindowTitle(caption+" - Checkers");

    // logo left
    QLabel* logo = new QLabel(dlg);
    logo->setPixmap(QPixmap("./icons/dialog.png"));

    // text editor
    QTextEdit* te = new QTextEdit(text, dlg);
    te->setReadOnly(true);
    te->setMinimumWidth(_mainframe->width()-100);
    te->setMinimumHeight(_mainframe->height()-200);

    // close button
    QPushButton* button = new QPushButton(tr("&Close"), dlg);
    connect(button, SIGNAL(clicked()), dlg, SLOT(accept()));

    // Layout.
    QHBoxLayout* hb = new QHBoxLayout();
    hb->addWidget(logo, 0, Qt::AlignTop);
    hb->addWidget(te, 1);

    QHBoxLayout* hb_button = new QHBoxLayout();
    hb_button->addStretch();
    hb_button->addWidget(button);

    QVBoxLayout* vb = new QVBoxLayout(dlg);
    vb->addLayout(hb, 1);
    vb->addSpacing(5);
    vb->addLayout(hb_button);

    // go
    dlg->exec();
    delete dlg;
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    e->accept();
}

void MainWindow::initialize_board()
{
    _mainframe->initialize_board( true );
}

void MainWindow::fileNewSlot()
{
    if( newGameDialog->exec() == QDialog::Accepted ) {
        _mainframe->newGame( newGameDialog->engineThinkDepth(), 
                             ( newGameDialog->isRusselAndNorvig() ? 
                               Engine::RUSSELL_AND_NORVIG :
                               Engine::RICH_AND_KNIGHT ),
                             newGameDialog->outputUpdateAnalysis(),
                             newGameDialog->editPosition(), 
                             newGameDialog->switchColors() );
    }
}

void MainWindow::analyzeButtonClickedSlot()
{
    _mainframe->analyzeCurrentPosition();
}

void MainWindow::toggleNumbersButtonClickedSlot()
{
    if( _showNotation ) {
        _mainframe->setNotation( false, false );
        _showNotation = false;
    } else {
        _mainframe->setNotation( true, true );
        _showNotation = true;
    }
}

void MainWindow::workingSlot(bool working)
{
    bool disable = !working;

    gameNew->setEnabled(disable);

    _mainframe->setEnabled(disable);
}
