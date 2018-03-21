#include <QtGui>
#include <QLabel>
#include <QFrame>
#include <QTabWidget>
#include <QMessageBox>

#include <algorithm>
#include <vector>

#include <iterator>

#include "HistogramWidget.h"
#include "AnalysisWindow.h"
#include "CacheSimulationThread.h"
#include "CacheInput.h"
#include "CacheOutput.h"
#include "CacheException.h"

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace std;

AnalysisWindow::AnalysisWindow( QWidget* parent,
                                Qt::WindowFlags flags ) :
    QMdiSubWindow( parent, flags )
{
    setAttribute( Qt::WA_DeleteOnClose );

    temporalHistogramWidget = 0;
    spatialHistogramWidget = 0;

    replacementPolicyButtonGroup = 0;
    inputFileEdit = 0;
    hitOverheadEdit = 0;
    cycleTimeEdit = 0;
    missPenaltyEdit = 0;
    MValueSpinBox = 0;
    KValueSpinBox = 0;
    WordSizeSpinBox = 0;
    fileTypeCheckBox = 0;

    totalHitsLabel_temporal = 0;
    totalHitsLabel_spatial = 0;
    totalMissesLabel_temporal = 0;
    totalMissesLabel_spatial = 0;
    missRatioLabel_temporal = 0;
    missRatioLabel_spatial = 0;
    speedupLabel_temporal = 0;
    speedupLabel_spatial = 0;

    currentSpatialValueLabel = 0;

    createWidgets();
    setDefaultValues();
}

void AnalysisWindow::copyConfig( const AnalysisWindow& rhs )
{
    int checkedId = rhs.replacementPolicyButtonGroup->checkedId();
    if( checkedId != -1 ) {
        QAbstractButton* rb = replacementPolicyButtonGroup->button( checkedId );
        if( rb ) {
            rb->setChecked( true );
        }
    }

    temporalHistogramWidget->plotSequence( rhs.temporalHistogramWidget->getCurrentTemporalSequence() );
    spatialHistogramWidget->plotSequence( rhs.spatialHistogramWidget->getCurrentSpatialSequence() );

    inputFileEdit->setText( rhs.inputFileEdit->text() );

    hitOverheadEdit->setText( rhs.hitOverheadEdit->text() );
    cycleTimeEdit->setText( rhs.cycleTimeEdit->text() );
    missPenaltyEdit->setText( rhs.missPenaltyEdit->text() );
    MValueSpinBox->setValue( rhs.MValueSpinBox->value() );
    KValueSpinBox->setValue( rhs.KValueSpinBox->value() );
    WordSizeSpinBox->setValue( rhs.WordSizeSpinBox->value() );
    fileTypeCheckBox->setChecked(rhs.fileTypeCheckBox->isChecked());

    totalHitsLabel_temporal->setText( rhs.totalHitsLabel_temporal->text() );
    totalHitsLabel_spatial->setText( rhs.totalHitsLabel_spatial->text() );
    totalMissesLabel_temporal->setText( rhs.totalMissesLabel_temporal->text() );
    totalMissesLabel_spatial->setText( rhs.totalMissesLabel_spatial->text() );
    missRatioLabel_temporal->setText( rhs.missRatioLabel_temporal->text() );
    missRatioLabel_spatial->setText( rhs.missRatioLabel_spatial->text() );
    speedupLabel_temporal->setText( rhs.speedupLabel_temporal->text() );
    speedupLabel_spatial->setText( rhs.speedupLabel_spatial->text() );
}

void AnalysisWindow::closeEvent(QCloseEvent *event)
{
     event->accept();
}

void AnalysisWindow::createWidgets()
{
    QFrame* frame = new QFrame;
    setWidget( frame );
    
    temporalHistogramWidget = new HistogramWidget;
    spatialHistogramWidget = new HistogramWidget;

    //    int cints[] = {10,9,8,7,6,5,4,3,2,1};
    //    vector<int> ints( &cints[0], &cints[0] + (sizeof( cints ) / sizeof( cints[0] )) );
    //    spatialHistogramWidget->plotSequence( ints );

    //    xSlider = createSlider();
    //    ySlider = createSlider();
    //    zSlider = createSlider();

    //    connect(xSlider, SIGNAL(valueChanged(int)), histogramWidget, SLOT(setXRotation(int)));
    //    connect(histogramWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    //    connect(ySlider, SIGNAL(valueChanged(int)), histogramWidget, SLOT(setYRotation(int)));
    //    connect(histogramWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    //    connect(zSlider, SIGNAL(valueChanged(int)), histogramWidget, SLOT(setZRotation(int)));
    //    connect(histogramWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));
    connect( spatialHistogramWidget, SIGNAL( currentValue( const QString& ) ), this, SLOT( updateHistogramValue( const QString& ) ) );

    QVBoxLayout* statusLayout = new QVBoxLayout( frame );
    QHBoxLayout* mainLayout = new QHBoxLayout;//( frame );

    QGridLayout* gridLayout1 = new QGridLayout;
    QGridLayout* gridLayout2 = new QGridLayout;

    totalHitsLabel_temporal = new QLabel;
    totalHitsLabel_spatial = new QLabel;
    totalMissesLabel_temporal = new QLabel;
    totalMissesLabel_spatial = new QLabel;
    missRatioLabel_temporal = new QLabel;
    missRatioLabel_spatial = new QLabel;
    speedupLabel_temporal = new QLabel;
    speedupLabel_spatial = new QLabel;

    gridLayout1->addWidget( new QLabel( tr( "Total Hits:" ) ), 0, 0 );
    gridLayout1->addWidget( totalHitsLabel_temporal, 0, 1 );

    gridLayout1->addWidget( new QLabel( tr( "Total Misses:" ) ), 1, 0 );
    gridLayout1->addWidget( totalMissesLabel_temporal, 1, 1 );

    gridLayout1->addWidget( new QLabel( tr( "Miss Ratio:" ) ), 2, 0 );
    gridLayout1->addWidget( missRatioLabel_temporal, 2, 1 );

    gridLayout1->addWidget( new QLabel( tr( "Speedup:" ) ), 3, 0 );
    gridLayout1->addWidget( speedupLabel_temporal, 3, 1 );

    gridLayout2->addWidget( new QLabel( tr( "Total Hits:" ) ), 0, 0 );
    gridLayout2->addWidget( totalHitsLabel_spatial, 0, 1 );

    gridLayout2->addWidget( new QLabel( tr( "Total Misses:" ) ), 1, 0 );
    gridLayout2->addWidget( totalMissesLabel_spatial, 1, 1 );

    gridLayout2->addWidget( new QLabel( tr( "Miss Ratio:" ) ), 2, 0 );
    gridLayout2->addWidget( missRatioLabel_spatial, 2, 1 );

    gridLayout2->addWidget( new QLabel( tr( "Speedup:" ) ), 3, 0 );
    gridLayout2->addWidget( speedupLabel_spatial, 3, 1 );

    QTabWidget* tabs = new QTabWidget;

    QWidget* spatial_tab = new QWidget;
    QVBoxLayout* spatialLayout = new QVBoxLayout( spatial_tab );

    currentSpatialValueLabel = new QLabel;
    spatialLayout->addWidget( currentSpatialValueLabel );
    spatialLayout->addWidget( spatialHistogramWidget );
    spatialLayout->addStretch();
    spatialLayout->addLayout( gridLayout2 );

    tabs->addTab( spatial_tab, tr( "Spatial Histogram" ) );

    QWidget* temporal_tab = new QWidget;

    QVBoxLayout* temporalLayout = new QVBoxLayout( temporal_tab );

    temporalLayout->addWidget( temporalHistogramWidget );
    temporalLayout->addStretch();
    temporalLayout->addLayout( gridLayout1 );

    tabs->addTab( temporal_tab, tr( "Temporal Histogram" ) );

    QFrame* leftframe = new QFrame;
    QGridLayout* leftLayout = new QGridLayout( leftframe );

    QLabel* label1 = new QLabel( tr( "Input File Name" ) );
    QLabel* label2 = new QLabel( tr( "--Cache Input Parameters--" ) );
    QLabel* label3 = new QLabel( tr( "M" ) );
    QLabel* label4 = new QLabel( tr( "K" ) );
    QLabel* label9 = new QLabel( tr( "Word Size" ) );
    replacementPolicyButtonGroup = new QButtonGroup;
    QRadioButton* rbutton1 = new QRadioButton( "LRU" );
    QRadioButton* rbutton2 = new QRadioButton( "LFU" );
    QRadioButton* rbutton3 = new QRadioButton( "Random" );

    replacementPolicyButtonGroup->addButton( rbutton1, 0 );
    replacementPolicyButtonGroup->addButton( rbutton2, 1 );
    replacementPolicyButtonGroup->addButton( rbutton3, 2 );

    QLabel* label5 = new QLabel( tr( "--Timing Parameters--" ) );
    QLabel* label6 = new QLabel( tr( "Hit Overhead" ) );
    QLabel* label7 = new QLabel( tr( "Cycle Time" ) );
    QLabel* label8 = new QLabel( tr( "Miss Penalty" ) );

    QLabel* label10 = new QLabel( tr( "Replacement Policy" ) );

    inputFileEdit = new QLineEdit;
    QPushButton* button1 = new QPushButton( "..." );
    connect( button1, SIGNAL( clicked() ), this, SLOT( openFile() ) );

    fileTypeCheckBox = new QCheckBox( "Binary File" );

    MValueSpinBox = new QSpinBox;
    KValueSpinBox = new QSpinBox;

    KValueSpinBox->setRange( 64, 16384 );

    WordSizeSpinBox = new QSpinBox;
    WordSizeSpinBox->setRange( 1, 128 );

    hitOverheadEdit = new QLineEdit;
    cycleTimeEdit = new QLineEdit;
    missPenaltyEdit = new QLineEdit;

    leftLayout->addWidget( label1, 0, 0 );
    leftLayout->addWidget( inputFileEdit, 1, 0 );
    leftLayout->addWidget( button1, 1, 1 );

    leftLayout->addWidget(fileTypeCheckBox, 2, 0, 1, 2);


    leftLayout->addWidget( label2, 3, 0, 1, 2 );
    leftLayout->addWidget( label3, 4, 0 );
    leftLayout->addWidget( MValueSpinBox, 4, 1 );
    leftLayout->addWidget( label4, 5, 0 );
    leftLayout->addWidget( KValueSpinBox, 5, 1 );
    leftLayout->addWidget( label9, 6, 0 );
    leftLayout->addWidget( WordSizeSpinBox, 6, 1 );

    leftLayout->addWidget( label10, 7, 0, 1, 2 );
    leftLayout->addWidget( rbutton1, 8, 0, 1, 2 );
    leftLayout->addWidget( rbutton2, 9, 0, 1, 2 );
    leftLayout->addWidget( rbutton3, 10, 0, 1, 2 );

    leftLayout->addWidget( label5, 11, 0, 1, 2 );
    leftLayout->addWidget( label6, 12, 0 );
    leftLayout->addWidget( hitOverheadEdit, 12, 1 );

    leftLayout->addWidget( label7, 13, 0 );
    leftLayout->addWidget( cycleTimeEdit, 13, 1 );

    leftLayout->addWidget( label8, 14, 0 );
    leftLayout->addWidget( missPenaltyEdit, 14, 1 );

    runAnalysisButton = new QPushButton( tr( "Run Analysis" ) );

    connect( runAnalysisButton, SIGNAL( clicked() ), this, SLOT( runAnalysisSlot() ) );

    leftLayout->addWidget( runAnalysisButton, 15, 0 );

    stopAnalysisButton = new QPushButton( tr( "Stop" ) );

    connect( stopAnalysisButton, SIGNAL( clicked() ), this, SLOT( stopAnalysisSlot() ) );

    leftLayout->addWidget( stopAnalysisButton, 15, 1 );

    stopAnalysisButton->setEnabled( false );

    progressBar = new QProgressBar;
    //    progressBar->setRange( 0, 100 );
    //    progressBar->reset();

    leftLayout->addWidget( progressBar, 16, 0, 1, 2 );

    mainLayout->addWidget( leftframe );
    mainLayout->addWidget( tabs );

    setWindowTitle(tr("Analysis Window"));

    statusBar = new QStatusBar;

    statusLayout->addLayout( mainLayout );
    statusLayout->addWidget( statusBar );

}
void AnalysisWindow::openFile()
{

    if( !inputFileEdit ) {
        return;
    }

    QString file = QFileDialog::getOpenFileName( this );
    if( file.length() ) {
        inputFileEdit->setText( file );
    }
}
void AnalysisWindow::runAnalysisSlot()
{
    runAnalysis();
}
void AnalysisWindow::runAnalysis()
{
    // get these inputs from the "io" module

    string fileType = "ASCII";

    if( fileTypeCheckBox->isChecked() ) {
        fileType ="BIN";
    }

    try {

        boost::shared_ptr<CacheInputClass> input;
        if( fileType == "ASCII" ) {
            input.reset( new ASCIIfile( inputFileEdit->text().toStdString() ) );
        } else {
            input.reset( new BINfile( inputFileEdit->text().toStdString() ) );
        }

        QAbstractButton* button = replacementPolicyButtonGroup->checkedButton();
        QString replacementPolicy( "LRU" );
        if( button ) {
            replacementPolicy = button->text();
        }

        input->setInputs( inputFileEdit->text().toStdString(),
                          fileType,
                          WordSizeSpinBox->value(),
                          KValueSpinBox->value(), 
                          MValueSpinBox->value(),
                          cycleTimeEdit->text().toInt(),
                          replacementPolicy.toStdString(),
                          missPenaltyEdit->text().toInt(),
                          hitOverheadEdit->text().toInt(),
                          false );

        analysisThread.reset( new CacheSimulationThread( input ) );
    } catch( const CacheException& ex ) {
        QMessageBox msgBox;
        msgBox.setText( ex.what() );
        msgBox.exec();
        return;
    }

    runAnalysisButton->setEnabled( false );
    stopAnalysisButton->setEnabled( true );

    connect( analysisThread.get(), SIGNAL( statusMessage( const QString& ) ),
             this, SLOT( cacheAnalysisStatusMessage( const QString& ) ) );
    connect( analysisThread.get(), SIGNAL( progressUpdate( int ) ),
             this, SLOT( cacheAnalysisUpdate( int ) ) );
    connect( analysisThread.get(), SIGNAL( simulationComplete() ),
             this, SLOT( cacheAnalysisComplete() ) );

    analysisThread->start();
}
void AnalysisWindow::stopAnalysisSlot()
{
    stopAnalysis();
    progressBar->reset();
    statusBar->showMessage( "Analysis stopped" );
}
void AnalysisWindow::stopAnalysis()
{
    if( analysisThread ) {
        analysisThread->disconnect();
        analysisThread->stop();
        analysisThread->wait();
        analysisThread.reset();
    }

    stopAnalysisButton->setEnabled( false );
    runAnalysisButton->setEnabled( true );
}

void AnalysisWindow::cacheAnalysisStatusMessage( const QString& msg )
{
    statusBar->showMessage( msg );
}

void AnalysisWindow::updateHistogramValue( const QString& msg )
{
    statusBar->showMessage( msg );
    currentSpatialValueLabel->setText( msg );
}

void AnalysisWindow::cacheAnalysisUpdate( int what )
{
    progressBar->setValue( what );
}
void AnalysisWindow::cacheAnalysisComplete()
{
    boost::shared_ptr<const CacheOutputClass> outp=analysisThread->results();

    if( outp ) {
        vector<int> referenceCounts;
        for( int i = 0; i < (int)outp->words.size(); ++i ) {
            referenceCounts.push_back( outp->words[i].integerCountReferenced );
        }

        sort( referenceCounts.begin(), referenceCounts.end(), std::greater<int>() );

        spatialHistogramWidget->plotSequence( referenceCounts );

        updateStatistics(outp->countTotal,outp->countNumHits, outp->countNumMisses, outp->speedup);
    }

    stopAnalysis();
}

void AnalysisWindow::updateStatistics( unsigned int total,
                                       unsigned int hits,
                                       unsigned int misses,
                                       float speedup )
{
    totalHitsLabel_temporal->setNum( static_cast<int>(hits) );
    totalHitsLabel_spatial->setNum( static_cast<int>(hits) );

    totalMissesLabel_temporal->setNum( static_cast<int>(misses) );
    totalMissesLabel_spatial->setNum( static_cast<int>(misses) );

    missRatioLabel_temporal->setNum( static_cast<double>(misses)/total );
    missRatioLabel_spatial->setNum( static_cast<double>(misses)/total );

    speedupLabel_temporal->setNum( static_cast<double>(speedup) );
    speedupLabel_spatial->setNum( static_cast<double>(speedup) );
}

void AnalysisWindow::setDefaultValues()
{
    if( spatialHistogramWidget )
        spatialHistogramWidget->plotSequence( vector<int>() );

    if( temporalHistogramWidget )
        temporalHistogramWidget->plotSequence( vector<int>() );

    if( replacementPolicyButtonGroup ) {
        QList<QAbstractButton*> buttons = replacementPolicyButtonGroup->buttons();
        if( !buttons.isEmpty() ) {
            buttons.first()->setChecked( true );
        }
    }

    if( inputFileEdit )
        inputFileEdit->clear();

    if( hitOverheadEdit ) {
        hitOverheadEdit->setText( QString().setNum(2) );
    }

    if( cycleTimeEdit ) {
        cycleTimeEdit->setText( QString().setNum(20) );
    }

    if( missPenaltyEdit ) {
        missPenaltyEdit->setText( QString().setNum(25) );
    }

    if( MValueSpinBox ) {
        MValueSpinBox->setValue( 16 );
    }

    if( KValueSpinBox ) {
        KValueSpinBox->setValue( 16 );
    }

    if( WordSizeSpinBox ) {
        WordSizeSpinBox->setValue( 64 );
    }

    if( progressBar ) {
        progressBar->reset();
    }
}


/*
QSlider* AnalysisWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}
*/
