#pragma once
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QKeyEvent>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QLabel>
#include <QWidget>
#include <QSemaphore>
#include <QSettings>
#include <QTextStream>
#include <list>
#include <QStandardItemModel>
#include <QList>
#include <QCheckBox>
#include <QLayout>
#include <QListWidget>
#pragma region OpenCV

#include "cv.hpp"
#include "highgui.h"
using namespace cv;
#pragma comment(lib,"opencv_highgui2413d.lib")
#pragma comment(lib,"opencv_imgproc2413d.lib")
#pragma comment(lib,"opencv_core2413d.lib")
#pragma comment(lib,"opencv_video2413d.lib")
#pragma endregion OpenCV

//�Զ���ṹ��
struct DefineSave 
{
	QString name;
	QString path;
	QList<QRect> ImgObject;
	QList<QString> ImgObjectSample;
};

class QMyListWidget : public QListWidget
{
	Q_OBJECT
		signals:
	void DefineMouseMove(QMouseEvent *event);
public:
	QMyListWidget(QWidget *parent);
	~QMyListWidget();
protected:
	//��д����������������ɴӸò�������ק��ȥ�Ĳ���.
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	//��¼��ק�����.
	QPoint m_dragPoint;
	//��¼����ק����.
	QListWidgetItem *m_dragItem;
};