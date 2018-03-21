#include <QThread>
#include <QTime>
#include <QMetaType>

#include <vector>

#include <boost/shared_ptr.hpp>

class CacheInputClass;
class CacheOutputClass;
class CacheAnalysis;

class CacheSimulationThread : public QThread {

    Q_OBJECT

public:
    CacheSimulationThread( boost::shared_ptr<CacheInputClass> inputs );

    void run();

    void stop() { m_stopped = true; }
    void pause() { m_pause = true; }
    void resume() { m_pause = false; }

    bool stopped() const { return m_stopped; }
    bool paused() const { return m_pause; }
    bool isPaused() const { return m_is_paused; }

    int timeElapsed() const { return m_time_elapsed; }

    boost::shared_ptr<const CacheOutputClass> results() const;

signals:

    void statusMessage( const QString& );
    void progressUpdate( int percent_complete );
    void simulationComplete();

protected:

    bool m_stopped;
    bool m_pause;
    bool m_is_paused;

    // members for managing statistics

    int m_time_elapsed;
    QTime timer;

    boost::shared_ptr<CacheInputClass> m_inputs;
    boost::shared_ptr<CacheAnalysis> m_analysis;
};
