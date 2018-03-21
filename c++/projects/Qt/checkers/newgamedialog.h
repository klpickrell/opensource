#ifndef NEWGAMEDLG_H
#define NEWGAMEDLG_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>


class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    NewGameDialog( QWidget* parent );
    ~NewGameDialog();

private slots:

    void cancelButtonClickedSlot();
    void okButtonClickedSlot();

public:

    int engineThinkDepth() const { return _engineDepthSB->value(); }
    bool editPosition() const { return _editPositionCB->isChecked(); }
    bool switchColors() const { return _switchColorsCB->isChecked(); }
    bool isRusselAndNorvig() const { return _russelAndNorvig->isChecked(); }
    bool outputUpdateAnalysis() const { return _analysisOutputCB->isChecked(); }


private:
    QWidget* createEnginePanel();
    QWidget* createButtonsPanel();

private:

    QCheckBox* _editPositionCB;
    QCheckBox* _switchColorsCB;
    QCheckBox* _analysisOutputCB;
    QSpinBox*  _engineDepthSB;

    QRadioButton* _russelAndNorvig;
    QRadioButton* _richAndKnight;
};

#endif

