#include "AllRelay.h"


QMyListWidget::QMyListWidget(QWidget *parent)
	: QListWidget(parent)
{
	//设置QListWidget接受拖拽.
	this->setAcceptDrops(true);
}

QMyListWidget::~QMyListWidget()
{

}
//重写鼠标点击操作.
void QMyListWidget::mousePressEvent(QMouseEvent *event)
{
	QListWidget::mousePressEvent(event);
}

void QMyListWidget::mouseMoveEvent(QMouseEvent *event)
{
	emit DefineMouseMove(event);
	QListWidget::mouseMoveEvent(event);
}
