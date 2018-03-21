#include <QDebug>
#include <QApplication>
#include <QEvent>
#include <QMetaType>

#include <sstream>
#include <algorithm>

#include <unistd.h>

#include "engine.h"

using namespace std;

Engine::Engine( int max_depth, 
                Engine::Algorithm algorithm,
                bool outputAnalysis ) :
    _algorithm( algorithm ),
    _outputAnalysis( outputAnalysis )
{
   _move_number = 0;
   _max_depth = max_depth;

   qRegisterMetaType< Board >( "Board" );
   qRegisterMetaType< Path >( "Path" );
   qRegisterMetaType< Board::Move >( "Move" );
}

Engine::~Engine()
{
    stop();
    wait();

    if( _thread ) {
        disconnect( _thread.get() );
    }
}

void Engine::think( const Board& position, int move_number )
{
    stop();
    wait();

    if( _thread ) {
        disconnect( _thread.get() );
    }

    if( _algorithm == Engine::RICH_AND_KNIGHT ) {

        _thread.reset( new RichAndKnightMinimax( this, 
                                                 position,
                                                 boost::shared_ptr< DepthStrategy >( new BasicDepthStrategy( _max_depth ) ),
                                                 //boost::shared_ptr< EvaluationStrategy >( new BasicEvaluationStrategy ),
                                                 boost::shared_ptr< EvaluationStrategy >( new WeightBasedEvaluationStrategy( 5, .2, .1 ) ),
                                                 boost::shared_ptr< MovegenStrategy >( new BasicMovegenStrategy ),
                                                 _outputAnalysis ) );
        connect( _thread.get(), SIGNAL( analysisUpdate( const Board&, const Path&, float ) ),
                 this, SLOT( threadAnalysisUpdateSlot( const Board&, const Path&, float ) ) );

        connect( _thread.get(), SIGNAL( analysisComplete( const Board&, const Path&, float ) ),
                 this, SLOT( threadAnalysisCompleteSlot( const Board&, const Path&, float ) ) );

    } else if( _algorithm == Engine::RUSSELL_AND_NORVIG ) {

        _thread.reset( new RussellAndNorvigMinimax( this, 
                                                    position,
                                                    boost::shared_ptr< DepthStrategy >( new BasicDepthStrategy( _max_depth ) ),
                                                    //boost::shared_ptr< EvaluationStrategy >( new BasicEvaluationStrategy ),
                                                    boost::shared_ptr< EvaluationStrategy >( new WeightBasedEvaluationStrategy( 5, .2, .1 ) ),
                                                    boost::shared_ptr< MovegenStrategy >( new BasicMovegenStrategy ),
                                                    _outputAnalysis ) );

        connect( _thread.get(), SIGNAL( analysisUpdate( const Board&, const Path&, float ) ),
                 this, SLOT( threadAnalysisUpdateSlot( const Board&, const Path&, float ) ) );

        connect( _thread.get(), SIGNAL( analysisComplete( const Board&, const Path&, float ) ),
                 this, SLOT( threadAnalysisCompleteSlot( const Board&, const Path&, float ) ) );
    } else {
        qDebug("Engine::think received invalid algorithm type");
        return;
    }

    _move_number = move_number;
    _thread->start();
}


void Engine::stop()
{
    if( _thread ) {
        _thread->stop();
    }
}

void Engine::pause()
{
    if( _thread ) {
        _thread->pause();
    }
}

void Engine::resume()
{
    if( _thread ) {
        _thread->resume();
    }
}

void Engine::wait( unsigned int millis )
{
    if( _thread ) {
        if( _thread->wait( millis ) ) {
            qDebug( "thread returned from run in Engine::wait" );
        } else {
            ostringstream os;
            os << "timeout after " << millis << " milliseconds waiting on thread in Engine::wait";
            qDebug( os.str().c_str() );
        }
    }
}

void Engine::threadAnalysisUpdateSlot(const Board& position, 
                                      const Path& path, 
                                      float eval)
{
    string linestring = generateLineString( position,
                                            path,
                                            eval,
                                            _move_number+position.depth() );

    if( linestring != _last_update ) {
                
        _last_update = linestring;
        emit engineUpdate( linestring.c_str() );
    }
}

void Engine::threadAnalysisCompleteSlot(const Board& position, 
                                        const Path& path, 
                                        float eval)
{
    stop();
    wait();
        
    if( !path.empty() ) {
        // grab the evaluation and path from the thread
        string linestring = generateLineString( position,
                                                path,
                                                eval,
                                                _move_number+position.depth() );

        ostringstream os;
        int nodes = _thread->nodes_evaluated();
        float time = static_cast< float >( _thread->time_elapsed() );
        
        if( time <= 0 ) {
            time = 1e-17;
        }

        os << "depth=" << _max_depth << " ply, " << nodes << " nodes evaluated in " << time/1e3 << " sec: " << 1e3*(nodes/time) << "nodes/sec, " << linestring;

        Board::Move firstmove = *(path.begin());
        emit analysisDone( os.str().c_str(), firstmove );
    }

    disconnect( _thread.get() );
    _thread.reset();
}

string Engine::generateLineString( const Board& initial_position,
                                   const Path& path,
                                   double evaluation,
                                   int mnum )
{
    ostringstream line;
    line << "Eval=" << evaluation << ",  Moves=  ";

    int move_number = mnum;

    if( move_number % 2 == 0 ) {
        line << Board::moveNumberToString( move_number );
    }

#ifdef PATH_DEBUG_PRINT
    Board print_board = initial_position;
    for( Path::const_iterator it = path.begin();
         it != path.end();
         ++it ) {

        Board::BoardMove move = print_board.convertToBoardMove( (*it) );

        ostringstream debug;
        debug << "generateLineString path contents: " << move.from << "-" << move.to;
        qDebug( debug.str().c_str() );

        print_board.move( move.from, move.to );
    }
#endif

    Board current_board = initial_position;

    for( Path::const_iterator it = path.begin();
         it != path.end();
         ++it, move_number++ ) {

        if( move_number % 2 ) {
            line << Board::moveNumberToString( move_number );
        }
            
        Board::BoardMove move = current_board.convertToBoardMove( (*it) );

        if( current_board.isMultiJumpCapture( move ) ) {

            line << Board::toString( move.from, move.to, current_board[ move.from ] );

            // make the first jump
            if( !current_board.move( move.from, move.to ) ) {
                ostringstream err;
                err << "Engine::generateLineString detected invalid move in Path: " << Board::toString( move.from, move.to, current_board[ move.from ] ) << endl;
                qDebug( err.str().c_str() );
            }

            Board::BoardMove realmove = move;

            for( Path::const_iterator next_i = ++it; next_i != path.end(); ++next_i ) {

                Board::BoardMove next_move = current_board.convertToBoardMove( (*next_i) );
                if( !current_board.move( next_move.from, next_move.to ) ) {
                    ostringstream err;
                    err << "Engine::generateLineString detected invalid move in Path: " << Board::toString( move.from, move.to, current_board[ move.from ] ) << endl;
                    qDebug( err.str().c_str() );
                    break;
                }

                // this happens when a multi-jump capture is included
                if( next_move.from == realmove.to ) {

                    realmove.to = next_move.to;
                    line << "x" <<  next_move.to;

                } else {
                    break;
                }
            }

        } else {

            line << Board::toString( move.from, move.to, current_board[ move.from ] );
            if( !current_board.move( move.from, move.to ) ) {
                ostringstream err;
                err << "Engine::generateLineString detected invalid move in Path: " << Board::toString( move.from, move.to, current_board[ move.from ] ) << endl;
                qDebug( err.str().c_str() );
                continue;
            }
        }

        line << "        ";
        current_board.switchTurns();
    }

    return line.str();
}

void RichAndKnightMinimax::run()
{
    qDebug("RichAndKnightMinimax::run");

    timer.start();
    MinimaxResult result = minimax_ab( _initial_position,
                                       _evaluation_strategy->maximum(),
                                       _evaluation_strategy->minimum() );
    _time_elapsed = timer.elapsed();

    _best_evaluation = result.value;
    _best_path = result.path;

    qDebug("RichAndKnightMinimax completed");
    emit analysisComplete( _initial_position,
                           _best_path,
                           _best_evaluation );

    while( !stopped() ) {
        msleep( 10 );
        // someone tried to pause while we were busy sleeping
        if( paused() ) {
            _is_paused = true;
        }
    }
}

MinimaxResult RichAndKnightMinimax::minimax_ab( const Board& position,
                                                float use_thresh,
                                                float pass_thresh )
{
    while( paused() ) {
        _is_paused = true;
        msleep( 10 );
    }

    _is_paused = false;

    if( stopped() ) {
        return MinimaxResult( 0, Path() );
    }

    _nodes_evaluated++;

    if( deep_enough( position ) ) {
        float evaluation = evaluate( position );
        return MinimaxResult( evaluation, Path() );
    }

    Path moves = generate_moves( position );

    if( moves.empty() ) {
        float evaluation = evaluate( position );
        return MinimaxResult( evaluation, Path() );
    }


    Path current_best_path = Path();
    for( Path::iterator path = moves.begin();
         path != moves.end();
         ++path ) {

        Board next_position = position;
        Board::BoardMove next_move = next_position.convertToBoardMove( (*path) );

        if( !next_position.move( next_move.from, next_move.to ) ) {
            qDebug( "Move failure in minimax_ab, generate_moves generated an invalid move" );
        }

        MinimaxResult result( 0, Path() );
        if( position.isMultiJumpCapture( next_move ) ) {

            // the next move is a capture too, don't switch turns, but perform minimax 
            // on the resulting position which will perform and evaluate any subsequent
            // captures

            result = minimax_ab( next_position,
                                 use_thresh,
                                 pass_thresh );
        } else {

            next_position.switchTurns();

            next_position.setDepth( position.depth() + 1 );
            result = minimax_ab( next_position,
                                 -pass_thresh,
                                 -use_thresh );
        }

        float new_value = result.value;
        if( new_value > pass_thresh ) {
            pass_thresh = new_value;
            current_best_path.assign( result.path.begin(), result.path.end() );
            current_best_path.push_front( (*path) );

            if( _outputAnalysis ) {
                emit analysisUpdate( position, current_best_path, pass_thresh );
            }
        }

        if( pass_thresh >= use_thresh ) {
            return MinimaxResult( pass_thresh, current_best_path );
        }
    }

    _best_evaluation = pass_thresh;
    _best_path = current_best_path;

    return MinimaxResult( pass_thresh, current_best_path );
}

void RussellAndNorvigMinimax::run()
{
    qDebug("RussellAndNorvigMinimax::run");

    timer.start();
    MinimaxResult result = alpha_beta_search( _initial_position );

    _time_elapsed = timer.elapsed();

    _best_evaluation = result.value;
    _best_path = result.path;

    qDebug("RussellAndNorvigMinimax completed");

    emit analysisComplete( _initial_position,
                           _best_path,
                           _best_evaluation );

    while( !stopped() ) {
        msleep( 10 );
        // someone tried to pause while we were busy sleeping
        if( paused() ) {
            _is_paused = true;
        }
    }
}

MinimaxResult RussellAndNorvigMinimax::max_value( const Board& position, float alpha, float beta )
{
    while( paused() ) {
        _is_paused = true;
        msleep( 10 );
    }

    _is_paused = false;

    if( stopped() ) {
        return MinimaxResult( 0, Path() );
    }

    _nodes_evaluated++;

    if( deep_enough( position ) ) {
        float evaluation = evaluate( position );
        return MinimaxResult( evaluation, Path() );
    }

    Path moves = generate_moves( position );

    if( moves.empty() ) {
        float evaluation = evaluate( position );
        return MinimaxResult( evaluation, Path() );
    }

    Path current_best_path = Path();
    float v = _evaluation_strategy->minimum();
    for( Path::iterator path = moves.begin();
         path != moves.end();
         ++path ) {

        Board next_position = position;
        Board::BoardMove next_move = next_position.convertToBoardMove( (*path) );

        if( !next_position.move( next_move.from, next_move.to ) ) {
            qDebug( "Move failure in max_value, generate_moves generated an invalid move" );
        }

        MinimaxResult result( 0, Path() );
        if( position.isMultiJumpCapture( next_move ) ) {

            // the next move is a capture too, don't switch turns, but perform minimax 
            // on the resulting position which will perform and evaluate any subsequent
            // captures

            result = max_value( next_position,
                                alpha,
                                beta );
        } else {

            next_position.switchTurns();

            next_position.setDepth( position.depth() + 1 );
            result = min_value( next_position,
                                alpha,
                                beta );
        }

        if( result.value > v ) {
            v = result.value;
            current_best_path.assign( result.path.begin(), result.path.end() );
            current_best_path.push_front( (*path) );

            if( _outputAnalysis ) {
                emit analysisUpdate( position, current_best_path, result.value );
            }
        }

        if( v >= beta ) {

            return MinimaxResult( v, current_best_path );
        }

        alpha = max( alpha, v );
    }

    _best_evaluation = v;
    _best_path = current_best_path;

    return MinimaxResult( v, current_best_path );
}

MinimaxResult RussellAndNorvigMinimax::min_value( const Board& position, float alpha, float beta )
{
    while( paused() ) {
        _is_paused = true;
        msleep( 10 );
    }

    _is_paused = false;

    if( stopped() ) {
        return MinimaxResult( 0, Path() );
    }

    _nodes_evaluated++;

    if( deep_enough( position ) ) {
        float evaluation = evaluate( position );
        return MinimaxResult( evaluation, Path() );
    }

    Path moves = generate_moves( position );

    if( moves.empty() ) {
        float evaluation = evaluate( position );
        return MinimaxResult( evaluation, Path() );
    }

    Path current_best_path = Path();
    float v = _evaluation_strategy->maximum();
    for( Path::iterator path = moves.begin();
         path != moves.end();
         ++path ) {

        Board next_position = position;
        Board::BoardMove next_move = next_position.convertToBoardMove( (*path) );

        if( !next_position.move( next_move.from, next_move.to ) ) {
            qDebug( "Move failure in max_value, generate_moves generated an invalid move" );
        }

        MinimaxResult result( 0, Path() );
        if( position.isMultiJumpCapture( next_move ) ) {

            // the next move is a capture too, don't switch turns, but perform minimax 
            // on the resulting position which will perform and evaluate any subsequent
            // captures

            result = min_value( next_position,
                                alpha,
                                beta );
        } else {

            next_position.switchTurns();

            next_position.setDepth( position.depth() + 1 );
            result = max_value( next_position,
                                alpha,
                                beta );
        }

        if( result.value < v ) {
            v = result.value;
            current_best_path.assign( result.path.begin(), result.path.end() );
            current_best_path.push_front( (*path) );

            if( _outputAnalysis ) {
                emit analysisUpdate( position, current_best_path, result.value );
            }
        }

        if( v <= alpha ) {
            return MinimaxResult( v, current_best_path );
        }

        beta = min( beta, v );
    }

    _best_evaluation = v;
    _best_path = current_best_path;

    return MinimaxResult( v, current_best_path );
}

bool BasicDepthStrategy::deep_enough( const Board& position ) const
{
    return position.depth() >= max_depth() || position.isGameOver();
}

float BasicEvaluationStrategy::evaluate( const Board& position ) const
{
    float eval = 0.0;
    for( int i = 0; i < position.size(); i++ ) {

        if( position[i] == Board::WHITE_PIECE ) {
            eval += 1;
        } else if( position[i] == Board::WHITE_KING ) {
            eval += 4;
        } else if( position[i] == Board::BLACK_PIECE ) {
            eval -= 1;
        } else if( position[i] == Board::BLACK_KING ) {
            eval -= 4;
        }
    }

    return eval;
}

float WeightBasedEvaluationStrategy::evaluate( const Board& position ) const
{
    float eval = 
        pieceCountWeight() * calculatePieceCountDifference( position ) +
        squaresControlledWeight() * calculateSquaresControlledDifference( position ) +
        displacementWeight() * calculateDisplacementDifference( position );

    return eval;
}

// This calculates a simple differential of piece weights.  Equal numbers
// of pieces and kings should come out to 0.
int WeightBasedEvaluationStrategy::
calculatePieceCountDifference( const Board& position ) const
{
    int count = 0;
    for( int i = 0; i < position.size(); i++ ) {

        if( position[i] == Board::WHITE_PIECE ) {
            count += 1;
        } else if( position[i] == Board::WHITE_KING ) {
            count += 4;
        } else if( position[i] == Board::BLACK_PIECE ) {
            count -= 1;
        } else if( position[i] == Board::BLACK_KING ) {
            count -= 4;
        }
    }

    return count;
}

// This gives bonuses to each side for having more pieces with free squares
// in front of them.  This encourages central control.
int WeightBasedEvaluationStrategy::
calculateSquaresControlledDifference( const Board& position ) const
{
    int count = 0;
    for( int i = 0; i < position.size(); i++ ) {

        vector< Board::BoardIndex > adjacents = 
            position.getAdjacentSquares( Board::board_index( i ), position[i] );
        
        if( adjacents.empty() ) {
            continue;
        }

        if( position[i] == Board::WHITE_PIECE ||
            position[i] == Board::WHITE_KING ) {

            // give +1 to every free square in front of a piece or king
            for( vector< Board::BoardIndex >::iterator current = adjacents.begin();
                 current != adjacents.end();
                 ++current ) {

                if( position.isFree( (*current ) ) ) {
                    count += 1;
                }
            }

        } else if( position[i] == Board::BLACK_PIECE ||
                   position[i] == Board::BLACK_KING ) {

            for( vector< Board::BoardIndex >::iterator current = adjacents.begin();
                 current != adjacents.end();
                 ++current ) {

                if( position.isFree( (*current ) ) ) {
                    count -= 1;
                }
                
            }
        }
    }

    return count;
}

// This gives penalties to each side for number of pieces remaining
// on the original square side.  It encourages movement.
int WeightBasedEvaluationStrategy::
calculateDisplacementDifference( const Board& position ) const
{
    int displacement = 0;
    // these should all be black pieces in the initial position
    for( int i=0; i<12; i++ ) {

        if( position[i] == Board::BLACK_PIECE )
            displacement += 1;
    }

    // these should all be white pieces in the initial position
    for( int i=20; i<32; i++ ) { 
        if( position[i] == Board::WHITE_PIECE ) {
            displacement -= 1;
        }
    }

    return displacement;
}

Path BasicMovegenStrategy::generate_moves( const Board& position ) const
{
    Path path;
    vector< Board::Move > vmoves = position.getAllCurrentlyLegalMoves( position.getTurn() );

    Path moves;
    moves.assign( vmoves.begin(), vmoves.end() );

    for( Path::iterator move = moves.begin();
         move != moves.end();
         ++move ) {

        Board::BoardMove bmove = position.convertToBoardMove( (*move) );

        //        if( position.isCapture( bmove.from, bmove.to ) ) {
        if( bmove.type == Board::PIECE_CAPTURE ||
            bmove.type == Board::KING_CAPTURE ) {

            path.push_back( (*move) );
        }
    }

    if( path.empty() ) {
        path = moves;
    }
    
    return path;
}
