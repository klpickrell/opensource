#ifndef BOARDWIDGET__H
#define BOARDWIDGET__H

#include <QFrame>

#include "tilewidget.h"
#include "board.h"

class BoardWidget : public QFrame
{
    Q_OBJECT

public:
    BoardWidget(QWidget* parent);
    ~BoardWidget();

    void selectSquare(int square_num, bool is_on);

    void load_icons( bool reverse = false );
    void reset_icons();

    void setNotation(bool enabled, bool show_above);

    void reverseColors();
    void reset();
    void setSquareText( bool whiteOnBottom );

    void setCurrentBoard( const Board& board ) {
        _current_board = board;
    }

    void drawBoard();

    Board getCurrentBoard() const { return _current_board; }

    std::string getWhitePieceIconPath() const { return _white_piece_icon_path; }
    std::string getBlackPieceIconPath() const { return _black_piece_icon_path; }
    std::string getWhiteKingIconPath() const { return _white_king_icon_path; }
    std::string getBlackKingIconPath() const { return _black_king_icon_path; }

    QSize minimumSizeHint() const { return QSize( 8*32, 8*32 ); }

signals:
    void squareClicked(int);

private:

    TileWidget* _squares[64];

    QPixmap* _pattern1;
    QPixmap* _pattern2;
    QPixmap* _frame;

    QPixmap* _active_player1;
    QPixmap* _active_player2;
    QPixmap* _active_king1;
    QPixmap* _active_king2;

    QPixmap* _black_single;
    QPixmap* _white_single;
    QPixmap* _black_king;
    QPixmap* _white_king;

    Board _current_board;

    std::string _white_piece_icon_path;
    std::string _black_piece_icon_path;
    std::string _white_king_icon_path;
    std::string _black_king_icon_path;
    
};


#endif

