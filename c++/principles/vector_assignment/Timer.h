#ifndef TIMEOUT__H
#define TIMEOUT__H

#include <ctime>
#include <exception>

class TimerException : public std::exception {
public:

    TimerException( const std::string& what ) :
        _what( what )
    {}

    ~TimerException() throw() {}

    const char* what() const throw() { return _what.c_str(); }

private:

    std::string _what;
};

class Timer
{
public:

    Timer( double duration = 0.0 ) throw( TimerException )
    {
        if( duration < 0 ) {
            throw TimerException( "attempt to initialize Timer with negative duration" );
        }

        set( duration );
    }

    bool expired() const { return ( Timer::now() - _start_time > duration() ); }
    double elapsed() { return Timer::now() - _start_time; }
    void reset() { _start_time = Timer::now(); }
    double duration() const { return _duration; }
    void set( double d ) { _duration = d; reset(); }

    static double now()
    {
        struct timespec tp;
        clock_gettime( CLOCK_REALTIME, &tp );
        return tp.tv_sec + 1.0e-9 * tp.tv_nsec;
    }
    
    static double now_ns()
    {
        struct timespec tp;
        clock_gettime( CLOCK_REALTIME, &tp );
        return tp.tv_nsec;
    }
    
private:

    double _start_time;
    double _duration;
};


#endif
