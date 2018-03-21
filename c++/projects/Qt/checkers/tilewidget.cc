#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "tilewidget.h"

TileWidget::TileWidget(QWidget* parent,int i)
    : QWidget(parent)
{
    pixmap = new QPixmap( MAX_TILE, MAX_TILE );

    _index=i;

    m_pattern=NULL;
    m_checker=NULL;
    m_frame=NULL;

    show_frame = false;

    _showLabel = false;
}


void TileWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawPixmap(0, 0, *pixmap);

    p.end();
}


void TileWidget::mousePressEvent(QMouseEvent* me)
{
    if(me->button() != Qt::LeftButton)
	return;
    emit click(_index);
}


void TileWidget::draw()
{
    QPainter paint;
    paint.begin(pixmap);
    paint.setFont(font());

    if(m_pattern)
	paint.drawPixmap(0, 0, *m_pattern);

    // notation
    paint.setPen(Qt::white);
    QRect not_rect = paint.boundingRect(2, 2, 0, 0, Qt::AlignLeft, _label);
    if(_showLabelAbove) {
	if(m_checker)
	    paint.drawPixmap(0, 0, *m_checker);
	if(_showLabel) {
	    paint.fillRect(not_rect, Qt::black);
	    paint.drawText(not_rect, Qt::AlignTop|Qt::AlignLeft, _label);
	}
    } else {
	if(_showLabel)
	    paint.drawText(not_rect, Qt::AlignTop|Qt::AlignLeft, _label);
	if(m_checker)
	    paint.drawPixmap(0, 0, *m_checker);
    }

    if(show_frame)
	paint.drawPixmap(0, 0, *m_frame);

    paint.end();
    update();
}


void TileWidget::setFrame(QPixmap* xpm)
{
    m_frame = xpm;
}


void TileWidget::showFrame(bool b)
{
    show_frame = b;
    draw();
}


void TileWidget::setPicture(QPixmap* xpm)
{
    m_checker = xpm;
    draw();
}


void TileWidget::setPattern(QPixmap* xpm)
{
    m_pattern = xpm;
    draw();
}


void TileWidget::setLabel(const QString& str)
{
    _label=str;
    draw();
}


void TileWidget::showLabel(bool s, bool a)
{
    _showLabelAbove = a;
    _showLabel = s;
    draw();
}

