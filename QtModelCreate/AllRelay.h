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

#pragma region OpenCV

#include "cv.hpp"
#include "highgui.h"
using namespace cv;
#pragma comment(lib,"opencv_highgui2413d.lib")
#pragma comment(lib,"opencv_imgproc2413d.lib")
#pragma comment(lib,"opencv_core2413d.lib")
#pragma comment(lib,"opencv_video2413d.lib")
#pragma endregion OpenCV