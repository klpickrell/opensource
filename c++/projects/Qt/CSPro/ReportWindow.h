#ifndef REPORT_WINDOW__H
#define REPORT_WINDOW__H

#include <QDialog>

class ReportWindow : public QDialog
{
    Q_OBJECT

public:

    ReportWindow( QWidget* parent = 0 );


public:

    void createWidgets();
};

#endif
