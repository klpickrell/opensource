#ifndef SQUARE__H
#define SQUARE__H

#include <qwidget.h>
#include <qpixmap.h>

const int MAX_TILE = 64;

class TileWidget : public QWidget
{
    Q_OBJECT

public:
    TileWidget(QWidget*, int num);

    const QString& label() const { return _label; }
    void setLabel(const QString&);
    void showLabel(bool s, bool above);

    void showFrame(bool);
    void setFrame(QPixmap*);
    void setPicture(QPixmap*);
    void setPattern(QPixmap*);

    int number() const { return _index; }

    void fontUpdate() { draw(); }

    QSize minimumSizeHint() const { return QSize( 32, 32 ); }

signals:
    void click(int);

protected:

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

private:
    void draw();

    int _index;

    // pixmap = pattern + label + picture + frame;

    QPixmap* m_frame;
    QPixmap* m_checker;
    QPixmap* m_pattern;

    QString _label;
    bool _showLabel;
    bool _showLabelAbove;

    QPixmap* pixmap;

    bool show_frame;
};

#endif


