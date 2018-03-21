#ifndef BOARD__H
#define BOARD__H

#include <stdexcept>
#include <vector>

class BoardException : public std::exception
{
public:
    BoardException( const std::string& m ) :
        _msg( m ){}

    ~BoardException() throw() {}

    const char* what() const throw() { return _msg.c_str(); }

private:

    std::string _msg;
};

const int INTERNAL_BOARD_SIZE = 54;
const int BOARD_SIZE = 32;

class Board
{
public:

    typedef enum { WHITE, BLACK, EMPTY } Color;

    typedef enum { FREE_SPACE = -1,
                   WHITE_PIECE = 1, 
                   WHITE_KING, 
                   BLACK_PIECE, 
                   BLACK_KING,
                   NONE } PieceType;

    typedef enum { ILLEGAL = 0,
                   PIECE_MOVE = 1,
                   KING_MOVE = 2,
                   PIECE_CAPTURE = 3,
                   KING_CAPTURE = 4 } MoveType;

    static const int UPPER_LEFT = -6;
    static const int UPPER_RIGHT = -5;
    static const int LOWER_LEFT = 5;
    static const int LOWER_RIGHT = 6;

    class BoardIndex {
    public:
        explicit BoardIndex( int idx ) :
            _idx( idx ){}

    public:

        int to_int() const { return _idx; }

        BoardIndex operator+( int where ) const { int idx = _idx + where; return BoardIndex( idx ); }
        BoardIndex operator+( const BoardIndex& where ) const { int idx = _idx + where._idx; return BoardIndex( idx ); }
        BoardIndex& operator=( int where ) { _idx = where; return *this; }
        BoardIndex& operator=( const BoardIndex& rhs ) { _idx = rhs._idx; return *this; }
        bool operator==( const BoardIndex& rhs ) const { return _idx == rhs._idx; }
        bool operator!=( const BoardIndex& rhs ) const { return !( *this == rhs ); }

    private:
        int _idx;
    };

    class IndexProxy {
    public:
        IndexProxy( Board& b, int idx ) :
            _board_ref( b ),
            _idx( idx ){}

        IndexProxy& operator=( const IndexProxy& rhs ) {
            _board_ref._board[ _board_ref.board_index( _idx ).to_int() ] = rhs._board_ref._board[ rhs._board_ref.board_index( rhs._idx ).to_int() ];
            return *this;
        }

        IndexProxy& operator=( PieceType p ) {
            _board_ref._board[ _board_ref.board_index( _idx ).to_int() ] = p;
            return *this;
        }

        operator PieceType() const {
            return _board_ref._board[ _board_ref.board_index( _idx ).to_int() ];
        }

    private:
        Board& _board_ref;
        int _idx;
    };

    class BoardIndexProxy {
    public:
        BoardIndexProxy( Board& b, int idx ) :
            _board_ref( b ),
            _idx( idx ){}

        BoardIndexProxy& operator=( const BoardIndexProxy& rhs ) {
            _board_ref._board[ _idx ] = rhs._board_ref._board[ rhs._idx ];
            return *this;
        }

        BoardIndexProxy& operator=( PieceType p ) {
            _board_ref._board[ _idx ] = p;
            return *this;
        }

        operator PieceType() const {
            return _board_ref._board[ _idx ];
        }

    private:
        Board& _board_ref;
        int _idx;
    };

    class Move
    {
    public:

        Move() 
            : from( 0 ),
              to( 0 ),
              type( ILLEGAL )
        {}

        Move( const BoardIndex& f,
              const BoardIndex& t,
              Board::MoveType tp = ILLEGAL ) :
            from( f ),
            to( t ),
            type( tp ) 
        {}
        
        Board::BoardIndex from;
        Board::BoardIndex to;
        Board::MoveType   type;
    };

    class BoardMove
    {
    public:
        BoardMove( int f,
                   int t,
                   Board::MoveType tp = ILLEGAL ) :
            from( f ),
            to( t ),
            type( tp ) 
        {}
        
        int from;
        int to;
        Board::MoveType type;
    };


    class CaptureSequence
    {
    public:
        ~CaptureSequence(){}

        bool empty() const { return _indices.empty(); }
        BoardIndex first() const { 
            if( empty() ) {
                throw BoardException( "CaptureSequence::first called on empty sequence" );
            }

            return *(_indices.begin()); 
        }
        BoardIndex last() const { 
            if( empty() ) {
                throw BoardException( "CaptureSequence::last called on empty sequence" );
            }
            
            return *(_indices.end()-1);
        }

        std::vector< BoardIndex >::const_iterator begin() const {
            return _indices.begin();
        }

        std::vector< BoardIndex >::const_iterator end() const {
            return _indices.end();
        }

    private:

        CaptureSequence(){}

        void push_back( const BoardIndex& square ) {
            _indices.push_back( square );
        }

        friend class Board;

    private:

        std::vector< BoardIndex > _indices;
    };

public:

    Board();
    Board( const Board& rhs );
    Board& operator=( const Board& rhs );

    std::string last_error() const { return _last_error; }

public:

    static BoardIndex upper_left( int idx ) { return BoardIndex( board_index( idx ) + UPPER_LEFT ); }
    static BoardIndex upper_right( int idx ) { return BoardIndex( board_index( idx ) + UPPER_RIGHT ); }
    static BoardIndex lower_left( int idx ) { return BoardIndex( board_index( idx ) + LOWER_LEFT ); }
    static BoardIndex lower_right( int idx ) { return BoardIndex( board_index( idx ) + LOWER_RIGHT ); }

    static BoardIndex upper_left( const BoardIndex& idx ) { return BoardIndex( idx + UPPER_LEFT ); }
    static BoardIndex upper_right( const BoardIndex& idx ) { return BoardIndex( idx + UPPER_RIGHT ); }
    static BoardIndex lower_left( const BoardIndex& idx ) { return BoardIndex( idx + LOWER_LEFT ); }
    static BoardIndex lower_right( const BoardIndex& idx ) { return BoardIndex( idx + LOWER_RIGHT ); }

    void reset();
    int size() const { return BOARD_SIZE; }

    void  setTurn( Color t ) { _to_move = t; }
    Color getTurn() const { return _to_move; }
    void  switchTurns() {
        if( _to_move == WHITE ) {
            _to_move = BLACK;
        } else {
            _to_move = WHITE;
        }
    }

    static std::vector< BoardIndex > getAdjacentSquares( int i, PieceType ptype = WHITE_KING )
    {
        return getAdjacentSquares( board_index( i ), ptype );
    }
    static std::vector< BoardIndex > getAdjacentSquares( const BoardIndex& i, PieceType ptype = WHITE_KING );

    static bool isAdjacentSquare( int a, int b, PieceType ptype = WHITE_KING )
    {
        return isAdjacentSquare( board_index( a ), board_index( b ), ptype );
    }

    static bool isAdjacentSquare( const BoardIndex& a, const BoardIndex& b, PieceType ptype = WHITE_KING );

    // legality tests
    MoveType getMoveType( int from, int to ) const;
    MoveType getWhiteMoveType( int from, int to ) const;
    MoveType getBlackMoveType( int from, int to ) const;

    MoveType getKingMoveType( int from, int to ) const
    {
        return getKingMoveType( board_index( from ), board_index( to ) );
    }
    MoveType getKingMoveType( const BoardIndex& from, const BoardIndex& to ) const;
    

    bool isSingleJumpCapture( const BoardIndex& from, const BoardIndex& over ) const;

    bool isMultiJumpCapture( int from, int to, MoveType type ) const
    {
        return isMultiJumpCapture( BoardMove( from, to, type ) );
    }
    bool isMultiJumpCapture( const Board::BoardMove& move ) const;

    bool canPromote( int square ) const 
    { 
        return canPromote( board_index( square ) ); 
    }
    bool canPromote( const BoardIndex& square ) const;

    bool whiteCaptureExists() const;
    bool blackCaptureExists() const;

    // return true if this item can capture anything adjacent
    bool itemAtSquareCanCapture( int square ) const 
    {
        return itemAtSquareCanCapture( board_index( square ) );
    }
    bool itemAtSquareCanCapture( const BoardIndex& square ) const;

    // return true if the requested move is a capture
    bool isCapture( int from, int to ) const;
    bool isCapture( const BoardMove& move )
    {
        return isCapture( move.from, move.to );
    }

    Color getColor( int square ) const 
    {
        return getColor( board_index( square ) );
    }
    Color getColor( const BoardIndex& square ) const;

    bool isFree( int square ) const;
    bool isFree( const BoardIndex& square ) const;

    bool isEdgeSquare( int square ) const;
    bool isEdgeSquare( const BoardIndex& square ) const;

    bool isKing( int square ) const 
    {
        return isKing( board_index( square ) );
    }
    bool isKing( const BoardIndex& square ) const 
    {
        return ( (*this)[square] == WHITE_KING ||
                 (*this)[square] == BLACK_KING );
    }
    bool isPiece( int square ) const 
    {
        return isPiece( board_index( square ) );
    }
    bool isPiece( const BoardIndex& square ) const 
    {
        return ( (*this)[square] == WHITE_PIECE ||
                 (*this)[square] == BLACK_PIECE );
    }

    // moving the pieces
    bool move( int from, int to );
    bool move( const Move& move );

    static bool onBoard( int square );
    static bool onBoard( const BoardIndex& square );

    static bool isBackRank( int square, Color color )
    {
        return isBackRank( board_index( square ), color );
    }
    static bool isBackRank( const BoardIndex& square, Color color );

    bool isGameOver() const;

    std::vector< Move > getLegalMoves( int square ) const 
    {
        return getLegalMoves( board_index( square ) );
    }
    std::vector< Move > getLegalMoves( const BoardIndex& square ) const;

    std::vector< Move > getAllCurrentlyLegalMoves( Color which ) const;
    std::vector< Move > getAllCurrentlyLegalWhiteMoves() const { return getAllCurrentlyLegalMoves( WHITE ); }
    std::vector< Move > getAllCurrentlyLegalBlackMoves() const { return getAllCurrentlyLegalMoves( BLACK ); }

    int depth() const { return _depth; }
    void setDepth( int newdepth ) { _depth = newdepth; }

    // convert adjacent captures to from-square to-square format
    BoardMove convertToBoardMove( const Move& move ) const;

    static std::string toString( int from, int to, Board::PieceType type = WHITE_KING );
    static std::string moveNumberToString( int movenum );

private:

    bool moveWhite( int from, int to );
    bool moveBlack( int from, int to );

    bool makeKingMove( int from, int to );
    bool makeSingleJumpCapture( const BoardIndex& from, const BoardIndex& to );

    void promoteKings();

public:


    const IndexProxy operator[]( int idx ) const throw( BoardException ) {
        if( !onBoard( idx ) ) {
            throw BoardException( "index out of range" );
        }

        return IndexProxy( const_cast< Board& >( *this ), idx );
    }

    IndexProxy operator[]( int idx ) throw( BoardException ) {
        if( !onBoard( idx ) ) {
            throw BoardException( "index out of range" );
        }

        return IndexProxy( *this, idx );
    }

    const BoardIndexProxy operator[]( BoardIndex b ) const throw( BoardException ) {
        if( !onBoard( b ) ) {
            throw BoardException( "index out of range" );
        }

        return BoardIndexProxy( const_cast< Board& >( *this ), b.to_int() );
    }

    BoardIndexProxy operator[]( BoardIndex b ) throw( BoardException ) {
        if( !onBoard( b ) ) {
            throw BoardException( "index out of range" );
        }

        return BoardIndexProxy( *this, b.to_int() );
    }

    friend class IndexProxy;
    friend class BoardIndexProxy;

public:
    
    static BoardIndex board_index( int idx ) throw( BoardException ) {
        static const int i[]={6,7,8,9,11,12,13,14,17,18,19,20,22,23,24,25,
                              28,29,30,31,33,34,35,36,39,40,41,42,44,45,46,47};

        if( idx > 31 || idx < 0 ) {
            throw BoardException( "index out of range in board_index" );
        }

        return BoardIndex( i[ idx ] );
    }

    static int int_index( const BoardIndex& idx ) throw( BoardException ) {

        static const int i[]={
            -1,-1,-1,-1,-1,-1,0,1,2,3,		// 0-9 internal
            -1,4,5,6,7,-1,-1,8,9,10,		// 10-19
            11,-1,12,13,14,15,-1,-1,16,17,	// 20-29
            18,19,-1,20,21,22,23,-1,-1,24,	// 30-39
            25,26,27,-1,28,29,30,31,-1,-1,	// 40-49
            -1,-1,-1,-1};			// 50-53

        if( idx.to_int() > 53 || idx.to_int() < 0 ) {
            throw BoardException( "index out of range in int_index" );
        }

        if( i[ idx.to_int() ] < 0 ) {
            throw BoardException( "invalid BoardIndex passed to int_index" );
        }

        return i[ idx.to_int() ];
    }

private:

    Color _to_move;
    PieceType _board[ INTERNAL_BOARD_SIZE ];
    mutable std::string _last_error;
    int _depth;

    static PieceType _board_validator[ INTERNAL_BOARD_SIZE ];
};

#endif
