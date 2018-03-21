// This is the Board class which houses the rules verification
// code and move validation


#include "board.h"
#include <string.h>
#include <sstream>

using namespace std;

//
//  Internal Representation   External Representation
//
//  Board = 54 Fields:        Board = 32 Fields:
//  ------------------         ------------------
//  |  06  07  08  09|  Black  |  00  01  02  03|
//  |11  12  13  14  |         |04  05  06  07  |
//  |  17  18  19  20|         |  08  09  10  11|
//  |22  23  24  25  |         |12  13  14  15  |
//  |  28  29  30  31|         |  16  17  18  19|
//  |33  34  35  36  |         |20  21  22  23  |
//  |  39  40  41  42|         |  24  25  26  27|
//  |44  45  46  47  |  White  |28  29  30  31  |
//  ------------------         ------------------

Board::PieceType Board::_board_validator[ INTERNAL_BOARD_SIZE ];

Board::Board()
{
    reset();
}

Board::Board( const Board& rhs )
{
    _to_move = rhs._to_move;
    _depth = rhs._depth;
    memcpy( _board, rhs._board, INTERNAL_BOARD_SIZE*sizeof( PieceType ) );
}

Board& Board::operator=( const Board& rhs )
{
    _to_move = rhs._to_move;
    _depth = rhs._depth;
    memcpy( _board, rhs._board, INTERNAL_BOARD_SIZE*sizeof( PieceType ) );

    return *this;
}

void Board::reset() 
{
    // initialize the board verifier
    // the board verifier is used as a quick test to see whether a square is 
    // on the board or within the sparse region

    for( int i = 0; i < INTERNAL_BOARD_SIZE; i++ ) {
        _board_validator[i] = Board::NONE;
        _board[i] = Board::NONE;
    }

    for( int i = 0; i < size(); i++ ) {
        _board_validator[ board_index( i ).to_int() ] = FREE_SPACE;
    }

    // initialize the boards valid indices
    for( int i=0; i<12; i++ )
        (*this)[ i ] = BLACK_PIECE;
    for( int i=12; i<20; i++ )
        (*this)[ i ] = FREE_SPACE;
    for( int i=20; i<32; i++ )
        (*this)[ i ] = WHITE_PIECE;

    _to_move = BLACK;
    _depth = 0;
}

// retrieves adjacent squares to a given index
// prunes the adjacent squares based on whether a piece is on the rim, or is a king or 
// man
vector< Board::BoardIndex > Board::getAdjacentSquares( const BoardIndex& i, PieceType ptype )
{
    vector< BoardIndex > adjacent;
    
    if( ptype == WHITE_KING ||
        ptype == BLACK_KING ) {

        BoardIndex ul = upper_left( i );
        BoardIndex ur = upper_right( i );
        BoardIndex ll = lower_left( i );
        BoardIndex lr = lower_right( i );


        if( _board_validator[ ul.to_int() ] == FREE_SPACE )
            adjacent.push_back( ul );
        if( _board_validator[ ur.to_int() ] == FREE_SPACE )
            adjacent.push_back( ur );
        if( _board_validator[ ll.to_int() ] == FREE_SPACE )
            adjacent.push_back( ll );
        if( _board_validator[ lr.to_int() ] == FREE_SPACE )
            adjacent.push_back( lr );
    } else if( ptype == WHITE_PIECE ) {

        BoardIndex ul = upper_left( i );
        BoardIndex ur = upper_right( i );

        if( _board_validator[ ul.to_int() ] == FREE_SPACE )
            adjacent.push_back( ul );
        if( _board_validator[ ur.to_int() ] == FREE_SPACE )
            adjacent.push_back( ur );
    } else if( ptype == BLACK_PIECE ) {

        BoardIndex ll = lower_left( i );
        BoardIndex lr = lower_right( i );

        if( _board_validator[ ll.to_int() ] == FREE_SPACE )
            adjacent.push_back( ll );
        if( _board_validator[ lr.to_int() ] == FREE_SPACE )
            adjacent.push_back( lr );
    }


    return adjacent;
}

// returns true if a is an adjacent square to b
bool Board::isAdjacentSquare( const BoardIndex& a, const BoardIndex& b, PieceType ptype )
{
    vector< BoardIndex > adjacents = getAdjacentSquares( b, ptype );
    return find( adjacents.begin(), adjacents.end(), a ) != adjacents.end();
}

// returns true if the square is on the board
bool Board::onBoard( int square )
{
    if( square > 31 || square < 0 ) {
        return false;
    } else {
        return true;
    }
}
bool Board::onBoard( const BoardIndex& square )
{
    if( square.to_int() > 53 || square.to_int() < 0 ) {
        return false;
    } else {
        return _board_validator[ square.to_int() ] != Board::NONE;
    }
}

// returns true if a square is on the back rank
bool Board::isBackRank( const BoardIndex& square, Color color )
{
    bool is = false;
    switch( color )
        {
        case WHITE:
            if( square == board_index( 0 ) ||
                square == board_index( 1 ) ||
                square == board_index( 2 ) ||
                square == board_index( 3 ) ) {

                is = true;
            }

            break;
        case BLACK:
            if( square == board_index( 28 ) ||
                square == board_index( 29 ) ||
                square == board_index( 30 ) ||
                square == board_index( 31 ) ) {

                is = true;
            }
            break;
        }

    return is;
}

// returns true if a white capture exists
bool Board::whiteCaptureExists() const
{
    bool found = false;
    for( int i = 0; i < size(); i++ ) {
        if( getColor( board_index( i ) ) == WHITE ) {
            if( itemAtSquareCanCapture( i ) ) {
                found = true;
                break;
            }
        }
    }

    return found;
}

// returns true if a black capture exists
bool Board::blackCaptureExists() const
{
    bool found = false;
    for( int i = 0; i < size(); i++ ) {
        if( getColor( board_index( i ) ) == BLACK ) {
            if( itemAtSquareCanCapture( i ) ) {
                found = true;
                break;
            }
        }
    }

    return found;
}

// returns true if the item at square 'square' can capture anything
bool Board::itemAtSquareCanCapture( const BoardIndex& square ) const
{
    if( isFree( square ) ) {
        return false;
    }

    vector< BoardIndex > adjacents = getAdjacentSquares( square, (*this)[ square ] );

    for( vector< BoardIndex >::iterator it = adjacents.begin();
         it != adjacents.end();
         ++it ) {
        
        if( isSingleJumpCapture( square, (*it) ) ) {
            return true;
        }
    }

    return false;
}

// checks to see if the move from-to is a capture
bool Board::isCapture( int from, int to ) const
{
    MoveType move = getMoveType( from, to );
    return (move == PIECE_CAPTURE || move == KING_CAPTURE );
}

// checks to see if the given move is a multi-jump capture
bool Board::isMultiJumpCapture( const BoardMove& move ) const
{
    bool is = false;

    if( canPromote( board_index( move.from ) ) || !onBoard( move.to ) || !onBoard( move.from ) ) {
        return false;
    }

    if( move.type == PIECE_CAPTURE ||
        move.type == KING_CAPTURE ) {

        Board testboard = (*this);
        if( testboard.move( move.from, move.to ) ) {
            is = testboard.itemAtSquareCanCapture( move.to );
        }
    }

    return is;
}

// retrieves all legal moves in the position and returns them in a vector
vector< Board::Move > Board::getLegalMoves( const BoardIndex& square ) const
{
    vector< Move > legals;
            
    vector< BoardIndex > adjacents = getAdjacentSquares( square, (*this)[square] );
    for( vector< BoardIndex >::const_iterator it = adjacents.begin();
         it != adjacents.end();
         ++it ) {

        Move m( square, (*it) );
        if( isFree( (*it) ) ) {
            m.from = square;
            m.to = (*it);

            if( isPiece( square ) ) {
                m.type = PIECE_MOVE;
            } else if( isKing( square ) ) {
                m.type = KING_MOVE;
            }

            legals.push_back( m );
        } else if( isSingleJumpCapture( square, (*it) ) ) {
            m.from = square;
            m.to = (*it);

            if( isPiece( square ) ) {
                m.type = PIECE_CAPTURE;
            } else if( isKing( square ) ) {
                m.type = KING_CAPTURE;
            }

            legals.push_back( m );
        }
    }

    return legals;
}

// this gets all currently legal moves for the indicated color
vector< Board::Move > Board::getAllCurrentlyLegalMoves( Color color ) const
{
    vector< Move > legals;
    for( int i = 0; i < size(); i++ ) {
        if( getColor( board_index( i ) ) == color  ) {
            
            vector< BoardIndex > adjacents = getAdjacentSquares( i, (*this)[i] );
            for( vector< BoardIndex >::iterator it = adjacents.begin();
                 it != adjacents.end();
                 ++it ) {

                BoardIndex square( board_index( i ) );
                Move m( square, (*it) );
                if( isFree( (*it) ) ) {
                    m.from = square;
                    m.to = (*it);

                    if( isPiece( square ) ) {
                        m.type = PIECE_MOVE;
                    } else if( isKing( square ) ) {
                        m.type = KING_MOVE;
                    }

                    legals.push_back( m );
                } else if( isSingleJumpCapture( square, (*it) ) ) {
                    m.from = square;
                    m.to = (*it);

                    if( isPiece( square ) ) {
                        m.type = PIECE_CAPTURE;
                    } else if( isKing( square ) ) {
                        m.type = KING_CAPTURE;
                    }

                    legals.push_back( m );
                }

            }
        }
    }

    return legals;
}

// this checks to see if the game is over, i.e. no more legal moves
bool Board::isGameOver() const
{
    if( getTurn() == WHITE ) {
        vector< Move > moves = getAllCurrentlyLegalWhiteMoves();
        return moves.empty();
    } else {
        vector< Move > moves = getAllCurrentlyLegalBlackMoves();
        return moves.empty();
    }
}

// returns true if the item at 'square' can promote
bool Board::canPromote( const BoardIndex& square ) const
{
    if( (*this)[ square ] == WHITE_KING ||
        (*this)[ square ] == BLACK_KING ) {

        return false;
    }

    vector< Board::Move > moves = getLegalMoves( square );
    if( moves.empty() ) {

        return false;
    }

    Color color = getColor( square );

    for( vector< Board::Move >::iterator it = moves.begin();
         it != moves.end();
         ++it ) {

        switch( color ) {

        case WHITE:
            if( isBackRank( it->to, WHITE ) ||
                ( isSingleJumpCapture( it->from, it->to ) &&
                  isBackRank( upper_left( it->to ), WHITE ) ) ) {

                return true;
            }
            break;
        case BLACK:
            if( isBackRank( it->to, BLACK ) ||
                ( isSingleJumpCapture( it->from, it->to ) &&
                  isBackRank( upper_left( it->to ), BLACK ) ) ) {

                return true;
            }
            break;
        }

    }

    return false;
}

// returns the move type from-to: PIECE_MOVE, PIECE_CAPTURE, KING_MOVE, KING_CAPTURE
Board::MoveType Board::getMoveType( int from, int to ) const
{
    if( !onBoard( from ) || !onBoard( to ) ) {
        _last_error = "Those squares aren't on the board";
        return ILLEGAL;
    }

    if( getTurn() == WHITE ) {
        return getWhiteMoveType( from, to );
    } else {
        return getBlackMoveType( from, to );
    }
}

// same as above but for white only
Board::MoveType Board::getWhiteMoveType( int from, int to ) const
{

    MoveType _result = ILLEGAL;
    if( getColor( from ) != WHITE ) {
        _last_error = "That's not a white piece";
        return _result;
    }

    if( !isFree( to ) ) {
        _last_error = "That space isn't free";
        return _result;
    }
        
    if( (*this)[ from ] == WHITE_PIECE ) {
        // its a piece move

        // first check single square moves, then check captures
        if( board_index( to ) == upper_left( from ) ||
            board_index( to ) == upper_right( from ) ) {

            // this is the single square move case
            _result = PIECE_MOVE;
            return _result;

        } else {

            // check captures
                
            if( board_index( to ) == upper_left( upper_left( from ) ) &&
                isSingleJumpCapture( board_index( from ), upper_left( from ) ) ) {
                _result = PIECE_CAPTURE;
                return _result;
            } else if( board_index( to ) == upper_right( upper_right( from ) ) &&
                       isSingleJumpCapture( board_index( from ), upper_right( from ) ) ) {
                _result = PIECE_CAPTURE;
                return _result;
            } else {
                _last_error = "Can't jump there";
                return _result;
            }
        }

    } else {
        // its a king move
        return getKingMoveType( from, to );
    }

    _last_error = "Invalid move";
    return _result;
}

// same as above but for black only
Board::MoveType Board::getBlackMoveType( int from, int to ) const
{

    MoveType _result = ILLEGAL;
    if( getColor( from ) != BLACK ) {
        _last_error = "That's not a black piece";
        return _result;
    }

    if( !isFree( to ) ) {
        _last_error = "That space isn't free";
        return _result;
    }
        
    if( (*this)[ from ] == BLACK_PIECE ) {
        // its a piece move

        // first check single square moves, then check captures
        if( board_index( to ) == lower_left( from ) ||
            board_index( to ) == lower_right( from ) ) {

            // this is the single square move case
            _result = PIECE_MOVE;
            return _result;

        } else {

            // check captures

            if( board_index( to ) == lower_left( lower_left( from ) ) &&
                isSingleJumpCapture( board_index( from ), lower_left( from ) ) ) {
                _result = PIECE_CAPTURE;
                return _result;
            } else if( board_index( to ) == lower_right( lower_right( from ) ) &&
                       isSingleJumpCapture( board_index( from ), lower_right( from ) ) ) {
                _result = PIECE_CAPTURE;
                return _result;
            } else {
                _last_error = "Can't jump there";
                return _result;
            }
        }

    } else {
        // its a king move
        return getKingMoveType( from, to );
    }

    _last_error = "Invalid move";
    return _result;
}

Board::MoveType Board::getKingMoveType( const BoardIndex& from, const BoardIndex& to ) const
{
    MoveType _result = ILLEGAL;
    // first check single square moves, then check captures
    if( to == upper_left( from ) ||
        to == upper_right( from ) ||
        to == lower_left( from ) ||
        to == lower_right( from ) ) {

        // this is the single square move case
        _result = KING_MOVE;
        return _result;

    } else {

        // it must be a king capture

        // check captures
                
        if( to == upper_left( upper_left( from ) ) &&
            isSingleJumpCapture( from, upper_left( from ) ) ) {
            _result = KING_CAPTURE;
            return _result;
        } else if( to == upper_right( upper_right( from ) ) &&
                   isSingleJumpCapture( from, upper_right( from ) ) ) {
            _result = KING_CAPTURE;
            return _result;
        } else if( to == lower_left( lower_left( from ) ) &&
                   isSingleJumpCapture( from, lower_left( from ) ) ) {
            _result = KING_CAPTURE;
            return _result;
        } else if( to == lower_right( lower_right( from ) ) &&
                   isSingleJumpCapture( from, lower_right( from ) ) ) {
            _result = KING_CAPTURE;
            return _result;
        } else {
            _last_error = "Can't jump there";
        }
    }

    return _result;
}

// returns true if the checker at from can jump over the checker at 'over'
bool Board::isSingleJumpCapture( const BoardIndex& from, const BoardIndex& over ) const
{
    if( isFree( from ) || isEdgeSquare( over ) || isFree( over ) ) {
        return false;
    }

    // check colors for optimization to allow check for single piece directions first

    if( getColor( from ) == WHITE ) {
        if( over == upper_left( from ) ) {

            return ( isFree( upper_left( over ) ) &&
                     getColor( from ) != getColor( over ) );

        } else if( over == upper_right( from  ) ) {

            return ( isFree( upper_right( over ) ) &&
                     getColor( from ) != getColor( over ) );

        } else if( over == lower_left( from ) ) {

            return ( isFree( lower_left( over ) ) &&
                     getColor( from ) != getColor( over ) );

        } else if( over == lower_right( from ) ) {

            return ( isFree( lower_right( over ) ) &&
                     getColor( from ) != getColor( over ) );

        }
    } else {
        if( over == lower_left( from ) ) {

            return ( isFree( lower_left( over ) ) &&
                     getColor( from ) != getColor( over ) );

        } else if( over == lower_right( from ) ) {

            return ( isFree( lower_right( over ) ) &&
                     getColor( from ) != getColor( over ) );

        } else if( over == upper_left( from ) ) {

            return ( isFree( upper_left( over ) ) &&
                     getColor( from ) != getColor( over ) );

        } else if( over == upper_right( from  ) ) {

            return ( isFree( upper_right( over ) ) &&
                     getColor( from ) != getColor( over ) );

        }
    }

    return false;
}

// returns the color of the square
Board::Color Board::getColor( const BoardIndex& square ) const
{
    if( isFree( square ) )
        return EMPTY;

    if( (*this)[ square ] == WHITE_PIECE ||
        (*this)[ square ] == WHITE_KING ) {
        return WHITE;
    } else {
        return BLACK;
    }
}

// returns true if the square is free
bool Board::isFree( int square ) const 
{
    return (*this)[ square ] == FREE_SPACE;
}

bool Board::isFree( const BoardIndex& square ) const 
{
    return (*this)[ square ] == FREE_SPACE;
}

// returns true if the square is on the edge
bool Board::isEdgeSquare( int square ) const
{
    return isEdgeSquare( board_index( square ) );
}
bool Board::isEdgeSquare( const BoardIndex& square ) const
{
    if( square.to_int() <= 11 ||
        square.to_int() >= 42 ||
        square.to_int() == 22 ||
        square.to_int() == 33 ||
        square.to_int() == 20 ||
        square.to_int() == 31 ) {
        return true;
    } else {
        return false;
    }
}

// performs a single jump capture
bool Board::makeSingleJumpCapture( const BoardIndex& from, const BoardIndex& over )
{
    bool captured = false;

    if( isFree( from ) || isEdgeSquare( over ) || isFree( over ) ) {
        return false;
    }

    // check colors for optimization to allow check for single piece directions first

    if( getColor( from ) == WHITE ) {
        if( over == upper_left( from ) &&
            isFree( upper_left( over ) ) ) {

            (*this)[ upper_left( over ) ] = (*this)[ from ];
            captured = true;

        } else if( over == upper_right( from  ) &&
                   isFree( upper_right( over ) ) ) {

            (*this)[ upper_right( over ) ] = (*this)[ from ];
            captured = true;

        } else if( over == lower_left( from ) &&
                   isFree( lower_left( over ) ) ) {

            (*this)[ lower_left( over ) ] = (*this)[ from ];
            captured = true;

        } else if( over == lower_right( from ) &&
                   isFree( lower_right( over ) ) ) {

            (*this) [ lower_right( over ) ] = (*this)[ from ];
            captured = true;

        }
    } else {
        if( over == lower_left( from ) &&
            isFree( lower_left( over ) ) ) {

            (*this)[ lower_left( over ) ] = (*this)[ from ];
            captured = true;

        } else if( over == lower_right( from ) &&
                   isFree( lower_right( over ) ) ) {

            (*this) [ lower_right( over ) ] = (*this)[ from ];
            captured = true;

        } else if( over == upper_left( from ) &&
            isFree( upper_left( over ) ) ) {

            (*this)[ upper_left( over ) ] = (*this)[ from ];
            captured = true;

        } else if( over == upper_right( from  ) &&
                   isFree( upper_right( over ) ) ) {

            (*this)[ upper_right( over ) ] = (*this)[ from ];
            captured = true;

        }
    }

    if( captured ) {
        (*this)[ over ] = FREE_SPACE;
        (*this)[ from ] = FREE_SPACE;
    }

    return captured;
}

// makes the move from-to
bool Board::move( int from, int to )
{
    // perform the move
    bool moved = false;
    if( getTurn() == WHITE ) {
        moved = moveWhite( from, to );
    } else {
        moved = moveBlack( from, to );
    }

    if( moved ) {
        promoteKings();
    }

    return moved;
}

// makes the white move from-to
bool Board::moveWhite( int from, int to )
{
    if( !onBoard( from ) || !onBoard( to ) ) {
        return false;
    }

    if( getColor( from ) != WHITE ) {
        return false;
    }

    if( !isFree( to ) ) {
        return false;
    }
        
    if( (*this)[ from ] == WHITE_PIECE ) {
        // its a piece move

        // first check single square moves, then check captures
        if( board_index( to ) == upper_left( from ) ||
            board_index( to ) == upper_right( from ) ) {

            // this is the single square move case

            (*this)[ to ] = (*this)[ from ];
            (*this)[ from ] = FREE_SPACE;

            return true;

        } else {

            // check captures

            if( board_index( to ) == upper_left( upper_left( from ) ) &&
                isSingleJumpCapture( board_index( from ), upper_left( from ) ) ) {

                return makeSingleJumpCapture( board_index( from ), upper_left( from ) );

            } else if( board_index( to ) == upper_right( upper_right( from ) ) &&
                isSingleJumpCapture( board_index( from), upper_right( from ) ) ) {

                return makeSingleJumpCapture( board_index( from ), upper_right( from ) );
            } else {

                _last_error = "Can't jump there";
                return false;
            }
        }

    } else {
        return makeKingMove( from, to );
    }

    return false;
}

// makes the black move from-to
bool Board::moveBlack( int from, int to )
{
    if( !onBoard( from ) || !onBoard( to ) ) {
        return false;
    }

    if( getColor( from ) != BLACK ) {
        return false;
    }

    if( !isFree( to ) ) {
        return false;
    }
        
    if( (*this)[ from ] == BLACK_PIECE ) {
        // its a piece move

        // first check single square moves, then check captures
        if( board_index( to ) == lower_left( from ) ||
            board_index( to ) == lower_right( from ) ) {

            // this is the single square move case

            (*this)[ to ] = (*this)[ from ];
            (*this)[ from ] = FREE_SPACE;

            return true;

        } else {

            // check captures

            if( board_index( to ) == lower_left( lower_left( from ) ) &&
                isSingleJumpCapture( board_index( from ), lower_left( from ) ) ) {

                return makeSingleJumpCapture( board_index( from ), lower_left( from ) );

            } else if( board_index( to ) == lower_right( lower_right( from ) ) &&
                       isSingleJumpCapture( board_index( from), lower_right( from ) ) ) {

                return makeSingleJumpCapture( board_index( from ), lower_right( from ) );
            } else {
                _last_error = "Can't jump there";
                return false;
            }
        }

    } else {

        return makeKingMove( from, to );
    }

    return false;
}

// makes the king move from-to
bool Board::makeKingMove( int from, int to )
{
    // its a king move

    // first check single square moves, then check captures
    if( board_index( to ) == upper_left( from ) ||
        board_index( to ) == upper_right( from ) ||
        board_index( to ) == lower_left( from ) ||
        board_index( to ) == lower_right( from ) ) {

        // this is the single square move case

        (*this)[ to ] = (*this)[ from ];
        (*this)[ from ] = FREE_SPACE;

        return true;

    } else {

        // it must be a king capture
                
        // check captures
                
        if( board_index( to ) == upper_left( upper_left( from ) ) &&
            isSingleJumpCapture( board_index( from ), upper_left( from ) ) ) {
            return makeSingleJumpCapture( board_index( from ), upper_left( from ) );
        } else if( board_index( to ) == upper_right( upper_right( from ) ) &&
                   isSingleJumpCapture( board_index( from ), upper_right( from ) ) ) {
            return makeSingleJumpCapture( board_index( from ), upper_right( from ) );
        } else if( board_index( to ) == lower_left( lower_left( from ) ) &&
                   isSingleJumpCapture( board_index( from ), lower_left( from ) ) ) {
            return makeSingleJumpCapture( board_index( from ), lower_left( from ) );
        } else if( board_index( to ) == lower_right( lower_right( from ) ) &&
                   isSingleJumpCapture( board_index( from ), lower_right( from ) ) ) {
            return makeSingleJumpCapture( board_index( from ), lower_right( from ) );
        } else {
            _last_error = "Can't jump there";
        }

    }

    return false;
}

// make every piece sitting on its furthest row a king
void Board::promoteKings()
{
    if( (*this)[ 0 ] == WHITE_PIECE ) {
        (*this)[ 0 ] = WHITE_KING;
    }

    if( (*this)[ 1 ] == WHITE_PIECE ) {
        (*this)[ 1 ] = WHITE_KING;
    }

    if( (*this)[ 2 ] == WHITE_PIECE ) {
        (*this)[ 2 ] = WHITE_KING;
    }

    if( (*this)[ 3 ] == WHITE_PIECE ) {
        (*this)[ 3 ] = WHITE_KING;
    }

    if( (*this)[ 28 ] == BLACK_PIECE ) {
        (*this)[ 28 ] = BLACK_KING;
    }

    if( (*this)[ 29 ] == BLACK_PIECE ) {
        (*this)[ 29 ] = BLACK_KING;
    }

    if( (*this)[ 30 ] == BLACK_PIECE ) {
        (*this)[ 30 ] = BLACK_KING;
    }

    if( (*this)[ 31 ] == BLACK_PIECE ) {
        (*this)[ 31 ] = BLACK_KING;
    }
}

// converts a Move (board indices) to a BoardMove (int indices) or the one you
// would play over the board and see in the analysis window
Board::BoardMove Board::convertToBoardMove( const Board::Move& move ) const
{
    Move result = move;
    if( Board::isAdjacentSquare( move.to, move.from ) ) {
        if( isSingleJumpCapture( move.from, move.to ) ) {
            if( move.to == upper_left( move.from ) ) {
                result.to = upper_left( move.to );
            } else if( move.to == upper_right( move.from ) ) {
                result.to = upper_right( move.to );
            } else if( move.to == lower_left( move.from ) ) {
                result.to = lower_left( move.to );
            } else if( move.to == lower_right( move.from ) ) {
                result.to = lower_right( move.to );
            }
        }
    }

    BoardMove bm( int_index( result.from ), int_index( result.to ) );
    bm.type = getMoveType( bm.from, bm.to );

    return bm;
}

string Board::toString( int from, int to, Board::PieceType type )
{
    ostringstream os;
    os << from;


    if( !Board::isAdjacentSquare( to, from, type ) ) {
        os << "x";
    } else {
        os << "-";
    }
    
    os << to;
    return os.str();
}

string Board::moveNumberToString( int move_number )
{
        
    int normalized = (move_number+1)/2;
    std::ostringstream os;
    os << normalized << ".";
    if( move_number % 2 == 0 ) {
        os << "..";
    }

    os << "  ";
    return os.str();
}

