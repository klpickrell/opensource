#include <stdlib.h>

#include <QLayout>
#include <QDebug>
#include <QFrame>
#include <QLabel>
#include <QGroupBox>

#include "newgamedialog.h"

NewGameDialog::NewGameDialog( QWidget* parent )
    : QDialog( parent )
{
    setModal( true );

    setWindowTitle( QString( "New Game" ) );


    QVBoxLayout* dialog_layout = new QVBoxLayout( this );

    dialog_layout->addWidget( createEnginePanel() );
    dialog_layout->addWidget( createButtonsPanel() );
}


NewGameDialog::~NewGameDialog()
{
}

QWidget* NewGameDialog::createEnginePanel()
{
    QFrame* frame = new QFrame();

    _engineDepthSB = new QSpinBox( this );
    _engineDepthSB->setMaximum( 14 );
    _engineDepthSB->setMinimum( 1 );
    _engineDepthSB->setValue( 5 );

    _editPositionCB = new QCheckBox(tr("Edit Position"), this);
    _switchColorsCB = new QCheckBox(tr("Reverse Colors"), this);
    _analysisOutputCB = new QCheckBox(tr("Output Analysis"), this);


    QGroupBox* algorithmGB = new QGroupBox( "Select Algorithm", this );
    _russelAndNorvig = new QRadioButton( "Russel And Norvig", algorithmGB );
    _richAndKnight = new QRadioButton( "Rich And Knight", algorithmGB );

    _russelAndNorvig->setChecked( true );

    QVBoxLayout* algorithm_layout = new QVBoxLayout( algorithmGB );
    algorithm_layout->addWidget( _russelAndNorvig );
    algorithm_layout->addWidget( _richAndKnight );

    QVBoxLayout* frame_layout = new QVBoxLayout( frame );

    frame_layout->addWidget( algorithmGB );
    frame_layout->addWidget( new QLabel( "Engine Think Depth (ply)" ) );
    frame_layout->addWidget( _engineDepthSB );
    frame_layout->addWidget( _editPositionCB );
    frame_layout->addWidget( _switchColorsCB );
    frame_layout->addWidget( _analysisOutputCB );
        
    return frame;
}

QWidget* NewGameDialog::createButtonsPanel()
{
    QFrame* panel = new QFrame();
    panel->setFrameStyle( QFrame::Raised );

    QPushButton* okButton = new QPushButton(tr("&Go"), this);
    okButton->setDefault(true);

    connect( okButton, SIGNAL(clicked()), this, SLOT(okButtonClickedSlot()));

    QPushButton* cancelButton = new QPushButton(tr("&Cancel"), this);
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( cancelButtonClickedSlot() ));

    QHBoxLayout* buttons_panel = new QHBoxLayout( panel );
    buttons_panel->addWidget( okButton );
    buttons_panel->addWidget( cancelButton );

    return panel;
}

void NewGameDialog::cancelButtonClickedSlot()
{
    reject();
}

void NewGameDialog::okButtonClickedSlot()
{
    accept();
}
