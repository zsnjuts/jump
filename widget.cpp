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

	cof = xiaomi4Cof;
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

	painter.setPen(Qt::black);
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(10);
	painter.setFont(font);
	painter.drawText(QPointF(10,20), QString("在小人底部中心点下左键,拖动到目标位置后放开"));
	painter.drawText(QPointF(10,40), QString("每一步跳完之后按空格键更新屏幕"));
	painter.drawText(QPointF(10,60), QString("cof=%1 (数字越大跳得越远,左右键大幅调整,上下键小幅调整)").arg(cof));
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
	double dx = abs(end.x()-begin.x());
	double dy = abs(end.y()-begin.y())*0.5771;
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
	else
	{
		switch(event->key())
		{
		case Qt::Key_Left: cof -= 0.1; break;
		case Qt::Key_Right: cof += 0.1; break;
		case Qt::Key_Up: cof += 0.01; break;
		case Qt::Key_Down: cof -= 0.01; break;
		default: ;
		}
		update();
		qDebug() << QString("cof=%1").arg(cof) << endl;
	}
}
