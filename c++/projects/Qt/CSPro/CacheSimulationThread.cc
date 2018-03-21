#include <math.h>

#include "CacheSimulationThread.h"
#include "CacheInput.h"
#include "CacheOutput.h"
#include "CacheAnalysis.h"

using namespace std;

CacheSimulationThread::CacheSimulationThread( boost::shared_ptr<CacheInputClass> input )
{
    m_inputs = input;
    m_analysis.reset( new CacheAnalysis( m_inputs ) );

    m_stopped = false;
    m_pause = false;
    m_is_paused = false;
    m_time_elapsed = 0;

    qRegisterMetaType<CacheOutputClass>( "CacheOutputClass" );
}

void CacheSimulationThread::run()
{
    int progress = 0;
    int last_progress = -1;

    emit statusMessage( QString( "Loading inputs..." ) );
    m_inputs->ParseInput();
    emit statusMessage( QString( "Running cache simulation" ) );

    try {
        m_analysis->StartAnalysis();
    } catch( const CacheException& ex ) {
        string s = "Cache analysis exception: ";
        s += ex.what();
        qDebug( s.c_str() );

        emit statusMessage( QString::fromStdString(s) );
        emit simulationComplete();
        return;
    }

    while( m_analysis->MoreWords() ) {

        while( paused() ) {
            m_is_paused = true;
            msleep( 10 );
        }

        m_is_paused = false;

        if( stopped() ) {
            break;
        }

        // Do some work
        m_analysis->ProcessNextWord();

        progress = m_analysis->percentComplete();

        if( last_progress < progress ) {
            last_progress = progress;
            emit progressUpdate( last_progress );
        }
    }

    m_analysis->updateSpeedupFactor();
    
    emit progressUpdate( 100 );

    emit statusMessage( QString( "Cache simulation complete" ) );
    emit simulationComplete();

    while( !stopped() ) {
        msleep( 10 );
        // someone tried to pause while we were busy sleeping
        if( paused() ) {
            m_is_paused = true;
        }
    }
}

boost::shared_ptr<const CacheOutputClass> CacheSimulationThread::results() const
{ 
    if( m_analysis ) {
        return m_analysis->output();
    } else {
        return boost::shared_ptr<const CacheOutputClass>();
    } 
}
