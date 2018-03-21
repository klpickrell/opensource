#include <QLayout>
#include <QDate>
#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <sstream>

#include "mainframe.h"
#include "engine.h"

using namespace std;

#define MAX_CMD_LEN		80
#define MOVE_PAUSE		1000

// this class is used to note differencies between moves.
class myDiff {
public:
    myDiff(int pos, int from, int to)
        : m_pos(pos), m_from(from), m_to(to) {}
    int m_pos;
    int m_from;
    int m_to;
};


MainFrame::MainFrame(QWidget* parent)
    : QFrame(parent)
{
    _selected_square = -1;

    QFrame* rightpanel = new QFrame( this );
    movesLog = new QTextEdit( rightpanel );
    movesLog->setReadOnly( true );

    QVBoxLayout* logvb = new QVBoxLayout( rightpanel );
    logvb->addWidget( new QLabel( "Moves", rightpanel ) );
    logvb->addWidget( movesLog );

    boardWidget = new BoardWidget( this );

    connect(boardWidget, SIGNAL(squareClicked(int)),
            this, SLOT(squareClickedSlot(int)));

    QHBoxLayout* toplayout = new QHBoxLayout();
    toplayout->addWidget( boardWidget );
    toplayout->addSpacing( 5 );
    toplayout->addWidget( rightpanel );

    analysisLog = new QTextEdit( this );
    analysisLog->setFixedHeight(100);
    analysisLog->setReadOnly(true);

    statusBar = new QStatusBar( this );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addLayout( toplayout );
    layout->addWidget( analysisLog );
    layout->addWidget( statusBar );
    layout->setSizeConstraint( QLayout::SetFixedSize );

    _whitePiecePixmap = 0;
    _whiteKingPixmap = 0;
    _blackPiecePixmap = 0;
    _blackKingPixmap = 0;
    _engine = 0;

    _edit_position = false;
}


MainFrame::~MainFrame()
{
    reset_pixmaps();
    reset_engine();
    QApplication::restoreOverrideCursor();
}

void MainFrame::reset_engine()
{
    if( _engine ) {
        _engine->stop();
        _engine->wait();
        delete _engine;
        _engine = 0;
    }
}

void MainFrame::allocate_engine( int depth, 
                                 Engine::Algorithm algorithm,
                                 bool outputAnalysis )
{
    if( _engine )
        return;

    _engine = new Engine( depth, algorithm, outputAnalysis );

    connect( _engine, SIGNAL( engineUpdate(const QString&) ),
             this, SLOT( engineUpdateSlot(const QString&) ) );

    connect( _engine, SIGNAL( analysisDone(const QString&, const Board::Move&) ),
             this, SLOT( analysisDoneSlot(const QString&, const Board::Move&) ) );
}



void MainFrame::setEnabled(bool b)
{
    boardWidget->setEnabled(b);
    if(b)
        setCursor(Qt::ArrowCursor);	// should be boardWidget bound.
    else
        setCursor(Qt::WaitCursor);
}


void MainFrame::newGame( int thinkdepth, 
                         Engine::Algorithm algorithm, 
                         bool outputAnalysis,
                         bool editposition, 
                         bool switchcolors )
{
    clear_analysis_log();
    clear_move_log();

    _selected_square = -1;

    //	emit working(true);
    boardWidget->reset();

    reset_engine();
    allocate_engine( thinkdepth, algorithm, outputAnalysis );

    _game_over = false;
    _move_number = 1;
    _edit_position = editposition;
}

void MainFrame::analyzeCurrentPosition()
{
    if( !_engine ) {
        return;
    }

    Board current_board = boardWidget->getCurrentBoard();
    
    emit working( true );

    _engine->think( current_board, _move_number );
}

void MainFrame::squareClickedSlot(int field_num)
{
    if( _game_over ) {
        return;
    }

    if( _selected_square == -1 ) {

        Board current_board = boardWidget->getCurrentBoard();

        if( !current_board.isFree( field_num ) ) {
            // take the selected piece off the board until it is moved
            _selected_square = field_num;
            _selected_piece = current_board[ _selected_square ];
            current_board[ _selected_square ] = Board::FREE_SPACE;

            switch( _selected_piece ) 
                {
                case Board::WHITE_PIECE:
                    QApplication::setOverrideCursor( QCursor( *_whitePiecePixmap ) );
                    break;
                case Board::WHITE_KING:
                    QApplication::setOverrideCursor( QCursor( *_whiteKingPixmap ) );
                    break;
                case Board::BLACK_PIECE:
                    QApplication::setOverrideCursor( QCursor( *_blackPiecePixmap ) );
                    break;
                case Board::BLACK_KING:
                    QApplication::setOverrideCursor( QCursor( *_blackKingPixmap ) );
                    break;
                }


            boardWidget->setCurrentBoard( current_board );
        }
    } else if( _selected_square != field_num ) {

        // put the selected piece back onto the board

        Board current_board = boardWidget->getCurrentBoard();
        current_board[ _selected_square ] = _selected_piece;

        Board::MoveType current_move_type = current_board.getMoveType( _selected_square, field_num );
        if( current_move_type != Board::ILLEGAL ) {
                
            // its legal, see if its a capture
            bool switchTurns = true;
            bool is_capture = (current_move_type == Board::PIECE_CAPTURE ||
                               current_move_type == Board::KING_CAPTURE );
            if( !is_capture ) {
                
                if( ( current_board.getTurn() == Board::WHITE  &&
                      current_board.whiteCaptureExists() ) ||
                    ( current_board.getTurn() == Board::BLACK ) &&
                    current_board.blackCaptureExists() ) {

                    statusBar->showMessage( "You must capture" );
                    current_board[ _selected_square ] = Board::FREE_SPACE;
                    boardWidget->setCurrentBoard( current_board );
                    boardWidget->drawBoard();
                    return;
                }
            }

            if( current_board.isMultiJumpCapture( Board::BoardMove( _selected_square, field_num, current_move_type ) ) ) {
                statusBar->showMessage( "Multi-jump capture" );
            } else if( is_capture ) {
                statusBar->showMessage( "Capture" );
            }

            bool was_promote = current_board.canPromote( _selected_square );
            if( !current_board.move( _selected_square, field_num ) ) {
                add_move_log( MainFrame::Warning, "Inconsistency in Board::move and Board::isLegalMove, there's a bug" );
            }

            if( was_promote ) {
                statusBar->showMessage( "Promotion" );
            }

            // if we can still capture
            if( is_capture && !was_promote ) {

                if( current_board.itemAtSquareCanCapture( field_num ) ) {
                    
                    _selected_square = field_num;

                    _selected_piece = current_board[ _selected_square ];
                    current_board[ _selected_square ] = Board::FREE_SPACE;

                    switchTurns = false;

                    statusBar->showMessage( "Keep Jumping!" );
                }
            }

            ostringstream os;
            os << Board::moveNumberToString( _move_number ) << current_board.toString( _selected_square, field_num );
            add_move_log( MainFrame::None, os.str().c_str() );

            if( switchTurns ) {

                current_board.switchTurns();
                _move_number++;

                if( !_edit_position ) {
                    emit working( true );
                    _engine->think( current_board, _move_number );
                }

                QApplication::restoreOverrideCursor();
                _selected_square = -1;

                if( current_board.isGameOver() ) {
                    if( current_board.getTurn() == Board::WHITE ) {
                        add_move_log( MainFrame::None, "0-1" );
                        add_move_log( MainFrame::None, "Black Wins!" );
                        statusBar->showMessage( "Black Wins!" );
                    } else {
                        add_move_log( MainFrame::None, "1-0" );
                        add_move_log( MainFrame::None, "White Wins!" );
                        statusBar->showMessage( "White Wins!" );
                    }

                    _game_over = true;
                }
            }   

        } else {

            current_board[ _selected_square ] = Board::FREE_SPACE;

            statusBar->showMessage( current_board.last_error().c_str() );
        }

        boardWidget->setCurrentBoard( current_board );

    } else {
        // same square was clicked twice

        Board current_board = boardWidget->getCurrentBoard();
        current_board[ _selected_square ] = _selected_piece;
        boardWidget->setCurrentBoard( current_board );

        _selected_square = -1;
        //            boardWidget->selectSquare( 0, false );
        QApplication::restoreOverrideCursor();
    }

    boardWidget->drawBoard();
}


void MainFrame::engineUpdateSlot( const QString& board_str )
{
    //    clear_log();
    add_analysis_log( MainFrame::System, board_str );
}

void MainFrame::analysisDoneSlot( const QString& board_str, const Board::Move& move )
{
    //    clear_log();
    QString str = "Analysis Complete: " + board_str;
    add_analysis_log( MainFrame::System, str );

    Board current_board = boardWidget->getCurrentBoard();
    Board::BoardMove bm = current_board.convertToBoardMove( move );
    current_board.move( bm.from, bm.to );

    current_board.switchTurns();

    boardWidget->setCurrentBoard( current_board );
    boardWidget->drawBoard();

    emit working( false );
}

void MainFrame::add_analysis_log(enum LogType type, const QString& text)
{
    QString str = text;
    str = str.replace('<', "&lt;");
    str = str.replace('>', "&gt;");

    QString tag_b, tag_e;
    switch(type) {
    case Error:	tag_b="<ul><pre>"; tag_e="</pre></ul>"; break;
    case Warning:	tag_b="<font color=\"red\"><b>"; tag_e="</b></font>"; break;
    case System:	tag_b="<font color=\"blue\">"; tag_e="</font>"; break;
    default:	break;
    }

    analysisLog->append(tag_b + str + tag_e);
    analysisLog->ensureCursorVisible();
}

void MainFrame::add_move_log(enum LogType type, const QString& text)
{
    QString str = text;
    str = str.replace('<', "&lt;");
    str = str.replace('>', "&gt;");

    QString tag_b, tag_e;
    switch(type) {
    case Error:	tag_b="<ul><pre>"; tag_e="</pre></ul>"; break;
    case Warning:	tag_b="<font color=\"red\"><b>"; tag_e="</b></font>"; break;
    case System:	tag_b="<font color=\"blue\">"; tag_e="</font>"; break;
    default:	break;
    }

    movesLog->append(tag_b + str + tag_e);
    movesLog->ensureCursorVisible();
}

void MainFrame::clear_analysis_log()
{
    analysisLog->clear();
}

void MainFrame::clear_move_log()
{
    movesLog->clear();
}

void MainFrame::setNotation(bool enabled, bool show_above)
{
    boardWidget->setNotation(enabled, show_above);
}
