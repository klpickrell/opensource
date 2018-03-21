#include <QtGui>
#include "HistogramWidget.h"

#include "ReportWindow.h"

ReportWindow::ReportWindow( QWidget* parent ) : 
    QDialog( parent )
{
    setAttribute( Qt::WA_DeleteOnClose );
    setWindowTitle( "Analysis Report" );
    resize( 300, 200 );

    createWidgets();
}

void ReportWindow::createWidgets()
{
    QGridLayout* gridLayout = new QGridLayout( this );

    gridLayout->addWidget( new QLabel( tr( "Anaylsis Comparison" ) ), 0, 0 );
    gridLayout->addWidget( new HistogramWidget(true), 1, 0, 1, 2 );

    gridLayout->addWidget( new QLabel( tr( "Total Hits:" ) ), 2, 0 );
    gridLayout->addWidget( new QLabel( tr( "2193" ) ), 2, 1 );

    gridLayout->addWidget( new QLabel( tr( "Total Misses:" ) ), 3, 0 );
    gridLayout->addWidget( new QLabel( tr( "379" ) ), 3, 1 );

    gridLayout->addWidget( new QLabel( tr( "Miss Ratio:" ) ), 4, 0 );
    gridLayout->addWidget( new QLabel( tr( "17%" ) ), 4, 1 );

    gridLayout->addWidget( new QLabel( tr( "Speedup:" ) ), 5, 0 );
    gridLayout->addWidget( new QLabel( tr( "58%" ) ), 5, 1 );
}
