#include "widget.h"
#include "ui_widget.h"
#include <cmath>

/*
 * 小米4的cof=3.4，华为mate7的cof=3.25
 *
 */

const double xiaomi4Cof = 3.4;
const double mate7Cof = 3.25;

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget),
	process(0)
{
	ui->setupUi(this);

	process.execute("adb shell screencap -p /sdcard/jump.png");
	process.execute("adb pull /sdcard/jump.png .");
	QImage img = QImage("jump.png").scaledToWidth(500);
	pixmap = QPixmap::fromImage(img);
	setFixedSize(img.width(), img.height());
}

Widget::~Widget()
{
	delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, pixmap);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
	if(event->button()!=Qt::LeftButton)
		return;
	begin = event->localPos();
	qDebug() << "begin=" << begin;
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button()!=Qt::LeftButton)
		return;
	end = event->localPos();
	qDebug() << "end=" << end;
	QPainter pp(&pixmap);
	pp.setPen(QPen(Qt::red, 10));
	pp.drawPoint(end);
	double dx = abs(end.x()-begin.x());
	double dy = abs(end.y()-begin.y())*0.5771;
	double cof = xiaomi4Cof; //距离转按压时间的比例系数
	QString cmd = QString("adb shell input swipe 100 100 100 100 %1").arg(int(cof*sqrt(dx*dx+dy*dy)+0.5));
	qDebug() << cmd;
	process.execute(cmd);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
	if(event->key()==Qt::Key_Space)
	{
		process.execute("adb shell screencap -p /sdcard/jump.png");
		process.execute("adb pull /sdcard/jump.png .");
		QImage img = QImage("jump.png").scaledToWidth(500);
		pixmap = QPixmap::fromImage(img);
		setFixedSize(img.width(), img.height());
		update();
	}
}
