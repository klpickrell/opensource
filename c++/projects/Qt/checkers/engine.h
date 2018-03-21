#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include <QEvent>
#include <QTime>
#include <QQueue>

#include "boost/shared_ptr.hpp"

#include "board.h"


class MinimaxThread;
typedef std::list< Board::Move > Path;
class MinimaxResult
{
public:
    MinimaxResult( float v, const Path& p ) 
    {
        value = v;
        path = p;
    }

    float value;
    Path path;
};

class Engine : public QObject
{
    Q_OBJECT

public:

    typedef enum {
        RICH_AND_KNIGHT,
        RUSSELL_AND_NORVIG,
    } Algorithm;

    Engine( int depth, Engine::Algorithm algorithm, bool outputanalysis = false );
    ~Engine();

    virtual void stop();
    virtual void pause();
    virtual void resume();

    virtual void think( const Board& position, int move_number );

    // generates a string for the move sequence applied to the initial position
    static std::string generateLineString( const Board& initial_position,
                                           const Path& path,
                                           double evaluation,
                                           int movenum );

    void wait( unsigned int millis = ULONG_MAX );

public slots:

    void threadAnalysisUpdateSlot(const Board& position, const Path& path, float eval);
    void threadAnalysisCompleteSlot(const Board& position, const Path& path, float eval);

signals:

    void engineUpdate(const QString&);
    void analysisDone(const QString&, const Board::Move&);

protected:

    boost::shared_ptr< MinimaxThread > _thread;
    int _move_number;
    Engine::Algorithm _algorithm;
    bool _outputAnalysis;

private:

    int _max_depth;
    std::string _last_update;
};

// implements the deep-enough algorithm
class DepthStrategy
{
public:
    virtual bool deep_enough( const Board& position ) const = 0;
};

// implements the static evaluation function
class EvaluationStrategy
{
public:
    // the static evaluation function, to be implemented in derived classes
    virtual float evaluate( const Board& position ) const = 0;
    // the minimum possible evaluation
    virtual float minimum() const = 0;
    // the maximum possible evaluation
    virtual float maximum() const = 0;
};

// implements the move generation strategy
class MovegenStrategy
{
public:
    virtual Path generate_moves( const Board& position ) const = 0;
};


class BasicDepthStrategy : public DepthStrategy
{
public:
    BasicDepthStrategy( int max_depth ) :
        _max_depth( max_depth )
    {}

    bool deep_enough( const Board& position ) const;

    int max_depth() const { return _max_depth; }

private:
    int _max_depth;
};

class BasicEvaluationStrategy : public EvaluationStrategy
{
public:
    BasicEvaluationStrategy()
    {}

    float evaluate( const Board& position ) const;

    float minimum() const { return -255; }
    float maximum() const { return 255; }
};

class WeightBasedEvaluationStrategy : public EvaluationStrategy
{
public:
    WeightBasedEvaluationStrategy( float piece_count_weight_p = 1,
                                   float squares_controlled_weight_p = 1,
                                   float displacement_weight_p = 1 )
    {
        _piece_count_weight = piece_count_weight_p;
        _squares_controlled_weight = squares_controlled_weight_p;
        _displacement_weight = displacement_weight_p;
    }

    float evaluate( const Board& position ) const;

    float minimum() const { return -255; }
    float maximum() const { return 255; }

    int calculatePieceCountDifference( const Board& position ) const;

    float pieceCountWeight() const { 
        return _piece_count_weight; 
    }

    int calculateSquaresControlledDifference( const Board& position ) const;

    float squaresControlledWeight() const { 
        return _squares_controlled_weight; 
    }
    
    int calculateDisplacementDifference( const Board& position ) const;

    float displacementWeight() const {
        return _displacement_weight;
    }

private:

    float _piece_count_weight;
    float _squares_controlled_weight;
    float _displacement_weight;
    
};

class BasicMovegenStrategy : public MovegenStrategy
{
public:
    BasicMovegenStrategy()
    {}

    Path generate_moves( const Board& position ) const;
};

class MinimaxThread : public QThread {

    Q_OBJECT

public:
    MinimaxThread( Engine* e, 
                   const Board& pos,
                   boost::shared_ptr< DepthStrategy > depth_strategy,
                   boost::shared_ptr< EvaluationStrategy > eval_strategy,
                   boost::shared_ptr< MovegenStrategy > movegen_strategy )

	: _engine(e), 
          _depth_strategy( depth_strategy ),
          _evaluation_strategy( eval_strategy ),
          _movegen_strategy( movegen_strategy ),
          _initial_position( pos )
    {
        _stopped = false;
        _pause = false;
        _is_paused = false;
        _nodes_evaluated = 0;
        _time_elapsed = 0;
    }

    virtual void run() = 0;

    void stop() { qDebug("MinimaxThread::stop called"); _stopped = true; }
    void pause() { _pause = true; }
    void resume() { _pause = false; }

    bool stopped() const { return _stopped; }
    bool paused() const { return _pause; }
    bool ispaused() const { return _is_paused; }

    virtual bool deep_enough( const Board& position ) const
    {
        return _depth_strategy->deep_enough( position );
    }

    virtual float evaluate( const Board& position ) const
    {
        return _evaluation_strategy->evaluate( position );
    }

    virtual Path generate_moves( const Board& position ) const
    {
        return _movegen_strategy->generate_moves( position );
    }

    float alpha_cutoff() const { return _alpha_cutoff; }
    void set_alpha_cutoff( float newv ) { _alpha_cutoff = newv; }

    float beta_cutoff() const { return _beta_cutoff; }
    void set_beta_cutoff( float newv ) { _beta_cutoff = newv; }

    std::list< Board::Move > best_path() const { return _best_path; }
    float best_evaluation() const { return _best_evaluation; }

    Board initial_position() const { return _initial_position; }

    int nodes_evaluated() const { return _nodes_evaluated; }
    int time_elapsed() const { return _time_elapsed; }

signals:

    void analysisUpdate(const Board& position, const Path& path, float eval);
    void analysisComplete(const Board& position, const Path& path, float eval);

protected:

    Engine* _engine;
    boost::shared_ptr< DepthStrategy > _depth_strategy;
    boost::shared_ptr< EvaluationStrategy > _evaluation_strategy;
    boost::shared_ptr< MovegenStrategy > _movegen_strategy;

    Board   _initial_position;

    Path  _best_path;
    float _best_evaluation;
    float _alpha_cutoff;
    float _beta_cutoff;

    bool _stopped;
    bool _pause;
    bool _is_paused;

    // members for managing statistics

    int _nodes_evaluated;
    int _time_elapsed;
    QTime timer;
};


class RichAndKnightMinimax : public MinimaxThread
{
public:

    RichAndKnightMinimax( Engine* engine,
                          const Board& position,
                          boost::shared_ptr< DepthStrategy > depth_strategy,
                          boost::shared_ptr< EvaluationStrategy > eval_strategy,
                          boost::shared_ptr< MovegenStrategy > movegen_strategy,
                          bool outputAnalysis ) :

        MinimaxThread( engine, position, depth_strategy, eval_strategy, movegen_strategy )
    {
        _outputAnalysis = outputAnalysis;
    }

    void run();

    MinimaxResult minimax_ab( const Board& position,
                              float use_threshold,
                              float pass_threshold );

private:

    bool _outputAnalysis;
};

class RussellAndNorvigMinimax : public MinimaxThread
{
public:
    RussellAndNorvigMinimax( Engine* engine,
                             const Board& position,
                             boost::shared_ptr< DepthStrategy > depth_strategy,
                             boost::shared_ptr< EvaluationStrategy > eval_strategy,
                             boost::shared_ptr< MovegenStrategy > movegen_strategy,
                             bool outputAnalysis ) :
        MinimaxThread( engine, position, depth_strategy, eval_strategy, movegen_strategy )
    {
        _outputAnalysis = outputAnalysis;
    }

    void run();

    MinimaxResult alpha_beta_search( const Board& position )
    {
        return max_value( position, 
                          _evaluation_strategy->minimum(),
                          _evaluation_strategy->maximum() );
    }

    MinimaxResult max_value( const Board& position, float alpha, float beta );
    MinimaxResult min_value( const Board& position, float alpha, float beta );

private:

    bool _outputAnalysis;
};

#endif

