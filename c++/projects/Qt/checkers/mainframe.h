#ifndef MAIN_FRAME__H
#define MAIN_FRAME__H

#include <QFrame>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QStatusBar>

#include <sstream>


#include "boardwidget.h"
#include "engine.h"
#include "board.h"

class Player;

class MainFrame : public QFrame
{
    Q_OBJECT

public:

    MainFrame(QWidget* parent);
    ~MainFrame();

    void newGame( int thinkdepth, 
                  Engine::Algorithm algorithm,
                  bool outputAnaylysis = false,
                  bool editposition = false, 
                  bool switchcolors = false );

    void setTheme();

    void setNotation(bool enabled, bool show_above);
 
    void initialize_board( bool reverse = false ) 
    { 
        boardWidget->load_icons( reverse ); 
        reset_pixmaps();

        _whitePiecePixmap = new QPixmap( boardWidget->getWhitePieceIconPath().c_str() );
        _whiteKingPixmap = new QPixmap( boardWidget->getWhiteKingIconPath().c_str() );
        _blackPiecePixmap = new QPixmap( boardWidget->getBlackPieceIconPath().c_str() );
        _blackKingPixmap = new QPixmap( boardWidget->getBlackKingIconPath().c_str() );
    }

    void reset_engine();

    void allocate_engine( int depth, Engine::Algorithm, bool outputAnalysis );
    void analyzeCurrentPosition();

public slots:
    virtual void setEnabled(bool);

signals:
    void working(bool);

private slots:

    void squareClickedSlot(int);
    void engineUpdateSlot(const QString& board_str);
    void analysisDoneSlot(const QString& board_str, const Board::Move&);

private:

    enum LogType {
        None,
        Error,
        Warning,
        System,
        User,
        Opponent,
    };

    void clear_move_log();
    void clear_analysis_log();

    void add_move_log( enum LogType type, const QString& text );
    void add_analysis_log( enum LogType type, const QString& text );

    void reset_pixmaps() {
        if( _whitePiecePixmap )
            delete _whitePiecePixmap;
        if( _whiteKingPixmap )
            delete _whiteKingPixmap;
        if( _blackPiecePixmap )
            delete _blackPiecePixmap;
        if( _blackKingPixmap )
            delete _blackKingPixmap;

        _whitePiecePixmap = 0;
        _whiteKingPixmap = 0;
        _blackPiecePixmap = 0;
        _blackKingPixmap = 0;
    }

private:

    BoardWidget* boardWidget;
    QStatusBar*  statusBar;

    int _selected_square;
    Board::PieceType _selected_piece;
    bool _game_over;
    int _move_number;

    bool _edit_position;

    QTextEdit* analysisLog;
    QTextEdit* movesLog;

    QPixmap* _whitePiecePixmap;
    QPixmap* _whiteKingPixmap;
    QPixmap* _blackPiecePixmap;
    QPixmap* _blackKingPixmap;
    
    Engine* _engine;
};


#endif

