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
#pragma region OpenCV

#include "cv.hpp"
#include "highgui.h"
using namespace cv;
#pragma comment(lib,"opencv_highgui2413d.lib")
#pragma comment(lib,"opencv_imgproc2413d.lib")
#pragma comment(lib,"opencv_core2413d.lib")
#pragma comment(lib,"opencv_video2413d.lib")
#pragma endregion OpenCV

//自定义结构体
struct DefineSave 
{
	QString name;
	QString path;
	QList<QRect> ImgObject;
	QList<int> ImgObjectSample;
};