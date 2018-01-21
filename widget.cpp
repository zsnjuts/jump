#include "widget.h"
#include "ui_widget.h"

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
	QString cmd = QString("adb shell input swipe 100 100 100 100 %1").arg(int(0.5+3.6*abs(end.x()-begin.x())));
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
