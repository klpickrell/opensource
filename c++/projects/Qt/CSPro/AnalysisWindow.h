#ifndef ANALYSIS_WINDOW__H
#define ANALYSIS_WINDOW__H

#include <QMdiSubWindow>

#include "boost/shared_ptr.hpp"

class HistogramWidget;
class QLineEdit;
class QSpinBox;
class QButtonGroup;
class QLabel;
class QProgressBar;
class QStatusBar;
class QCheckBox;

class CacheSimulationThread;
class QPushButton;

class AnalysisWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    AnalysisWindow( QWidget* parent = 0, Qt::WindowFlags flags = 0 );

    void copyConfig( const AnalysisWindow& copy );
    
    void updateStatistics( unsigned int total,
                           unsigned int hits,
                           unsigned int misses,
                           float speedup );

    void runAnalysis();
    void stopAnalysis();

protected:
    void closeEvent( QCloseEvent* event );

public slots:

    void runAnalysisSlot();
    void stopAnalysisSlot();
    void cacheAnalysisStatusMessage( const QString& );
    void cacheAnalysisUpdate( int );
    void cacheAnalysisComplete();
    void updateHistogramValue( const QString& );

private slots:

    void openFile();

private:

    void createWidgets();
    void setDefaultValues();

    HistogramWidget* spatialHistogramWidget;
    HistogramWidget* temporalHistogramWidget;

    QButtonGroup* replacementPolicyButtonGroup;
    QLineEdit* inputFileEdit;
    QLineEdit* hitOverheadEdit;
    QLineEdit* cycleTimeEdit;
    QLineEdit* missPenaltyEdit;
    QSpinBox*  MValueSpinBox;
    QSpinBox*  KValueSpinBox;
    QSpinBox*  WordSizeSpinBox;
    QCheckBox* fileTypeCheckBox;

    QLabel* totalHitsLabel_temporal;
    QLabel* totalHitsLabel_spatial;
    QLabel* totalMissesLabel_temporal;
    QLabel* totalMissesLabel_spatial;
    QLabel* missRatioLabel_temporal;
    QLabel* missRatioLabel_spatial;
    QLabel* speedupLabel_temporal;
    QLabel* speedupLabel_spatial;

    QLabel* currentSpatialValueLabel;

    QPushButton* runAnalysisButton;
    QPushButton* stopAnalysisButton;
    QProgressBar* progressBar;

    QStatusBar* statusBar;

    boost::shared_ptr<CacheSimulationThread> analysisThread;
    //    boost::shared_ptr<CacheThread> analysisThread;
};

#endif
