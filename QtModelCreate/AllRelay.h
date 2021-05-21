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
#ifdef DEBUG
#pragma comment(lib,"opencv_highgui3414d.lib")
#pragma comment(lib,"opencv_imgproc3414d.lib")
#pragma comment(lib,"opencv_imgcodecs3414d.lib")
#pragma comment(lib,"opencv_core3414d.lib")
#pragma comment(lib,"opencv_video3414d.lib")
#pragma comment(lib,"opencv_videoio3414d.lib")
#else
#pragma comment(lib,"opencv_highgui3414.lib")
#pragma comment(lib,"opencv_imgproc3414.lib")
#pragma comment(lib,"opencv_imgcodecs3414.lib")
#pragma comment(lib,"opencv_core3414.lib")
#pragma comment(lib,"opencv_video3414.lib")
#pragma comment(lib,"opencv_videoio3414.lib")
#endif
#pragma endregion OpenCV

//自定义结构体
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
	//重写下面两个函数来完成从该部件中拖拽出去的操作.
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	//记录拖拽的起点.
	QPoint m_dragPoint;
	//记录被拖拽的项.
	QListWidgetItem *m_dragItem;
};