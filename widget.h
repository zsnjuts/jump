#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QKeyEvent>
#include <QProcess>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	Ui::Widget *ui;
	QPixmap pixmap;
	QPointF begin;
	QPointF end;
	QProcess process;
	double cof; //距离转按压时间的比例系数
};

#endif // WIDGET_H
