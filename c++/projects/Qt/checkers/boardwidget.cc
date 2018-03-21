#include <QLayout>
#include <QDebug>

#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget* parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box|QFrame::Plain);
    for(int i=0; i<64; i++)
	_squares[i] = new TileWidget(this, i);

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setMargin(0);
    for(int i=0; i<4; i++) {
	for(int k=0; k<4; k++) {
            grid->addWidget(_squares[i*8+k+32], i*2,  k*2  );
            grid->addWidget(_squares[i*8+k   ], i*2,  k*2+1);
            grid->addWidget(_squares[i*8+k+4 ], i*2+1,k*2  );
            grid->addWidget(_squares[i*8+k+36], i*2+1,k*2+1);
        }
    }

    for(int i=0; i<32; i++)
        connect(_squares[i], SIGNAL(click(int)),
                this, SIGNAL(squareClicked(int)));


    _pattern1 = 0;
    _pattern2 = 0;
    _frame= 0;
    _black_single = 0;
    _white_single = 0;
    _black_king= 0;
    _white_king= 0;

    _white_piece_icon_path = "./themes/selected/manwhite.png";
    _black_piece_icon_path = "./themes/selected/manblack.png";
    _white_king_icon_path = "./themes/selected/kingwhite.png";
    _black_king_icon_path = "./themes/selected/kingblack.png";

    setSquareText( true );
}


BoardWidget::~BoardWidget()
{
    reset_icons();
}


void BoardWidget::load_icons( bool reverse )
{
    reset_icons();

    _pattern1 = new QPixmap("./themes/selected/tile1.png");
    _pattern2 = new QPixmap("./themes/selected/tile2.png");
    _frame= new QPixmap("./themes/selected/frame.png");
    _black_single = new QPixmap( _black_piece_icon_path.c_str() );
    _white_single = new QPixmap( _white_piece_icon_path.c_str() );
    _black_king= new QPixmap( _black_king_icon_path.c_str() );
    _white_king= new QPixmap( _white_king_icon_path.c_str() );

    if( reverse )
        reverseColors();

    for(int i=0; i<32; i++)
        _squares[i]->setPattern(_pattern2);
    for(int i=32; i<64; i++)
        _squares[i]->setPattern(_pattern1);
    for(int i=0; i<32; i++)
        _squares[i]->setFrame(_frame);

    setFixedSize(_active_player1->width()*8 + 2*frameWidth(),
                 _active_player1->height()*8 + 2*frameWidth());

    drawBoard();
}

void BoardWidget::reset_icons()
{
    if( _white_single ) {
        delete _white_single;
    }
    if( _black_single ) {
        delete _black_single;
    }
    if( _white_king ) {
        delete _white_king;
    }
    if( _black_king ) {
        delete _black_king;
    }
    if( _pattern1 ) {
        delete _pattern1;
    }
    if( _pattern2 ) {
        delete _pattern2;
    }
    if( _frame ) {
        delete _frame;
    }
}


void BoardWidget::reset()
{
    _current_board = Board();
    drawBoard();
}


void BoardWidget::setSquareText( bool whiteOnBottom )
{
    if( whiteOnBottom ) {

        for(int i=0; i<32; i++) {

            QString label;
            label.setNum( i );
            _squares[i]->setLabel( label );
        }

    } else {

        for(int i=0; i<32; i++) {

            QString label;
            label.setNum( 31-i );
            _squares[i]->setLabel( label );
        }
    }
}


void BoardWidget::drawBoard()
{
    for( int i = 0; i < _current_board.size(); i++ ) {
	switch( _current_board[i] ) {
	case Board::WHITE_PIECE:
            _squares[i]->setPicture(_active_player1);
            break;
	case Board::BLACK_PIECE:
            _squares[i]->setPicture(_active_player2);
            break;
	case Board::WHITE_KING:
            _squares[i]->setPicture(_active_king1);
            break;
	case Board::BLACK_KING:
            _squares[i]->setPicture(_active_king2);
            break;
	default:
            _squares[i]->setPicture( 0 );
	}
    }
}


void BoardWidget::reverseColors()
{
    if( _active_player1 != _white_single  ) {
	_active_player1 = _white_single;
	_active_player2 = _black_single;
	_active_king1= _white_king;
	_active_king2= _black_king;
    } else {
	_active_player1 = _black_single;
	_active_player2 = _white_single;
	_active_king1= _black_king;
	_active_king2= _white_king;
    }
}

void BoardWidget::setNotation(bool s, bool above)
{
    for(int i=0; i<32; i++)
        _squares[i]->showLabel(s, above);
}

// called when a square is clicked
void BoardWidget::selectSquare(int square_num, bool is_on)
{
    for(int i=0; i<32; i++) {
        if(i==square_num)
            _squares[i]->showFrame(is_on);
        else
            _squares[i]->showFrame(false);
    }
}
