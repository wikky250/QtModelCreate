#include "AllRelay.h"


QMyListWidget::QMyListWidget(QWidget *parent)
	: QListWidget(parent)
{
	//����QListWidget������ק.
	this->setAcceptDrops(true);
}

QMyListWidget::~QMyListWidget()
{

}
//��д���������.
void QMyListWidget::mousePressEvent(QMouseEvent *event)
{
	QListWidget::mousePressEvent(event);
}

void QMyListWidget::mouseMoveEvent(QMouseEvent *event)
{
	emit DefineMouseMove(event);
	QListWidget::mouseMoveEvent(event);
}
