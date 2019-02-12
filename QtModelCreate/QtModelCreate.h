#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtModelCreate.h"
#include "AllRelay.h"
#include "MultPlay.h"
class QtModelCreate : public QMainWindow
{
	Q_OBJECT
		signals :
	void Signal_ConvertPlay();
	void Signal_ConverttoPlay();
	void Signal_Play();
public:
	QtModelCreate(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtModelCreateClass ui;
	//加载路径
	QString m_SvideoPath;
	//判断是否为视频加载
	bool m_BisVideo;
	//多线程实例
	MultPlay *m_Play;
	//多线程进程
	QThread *m_PlayThread;
	QLabel *m_LabelShow;
	QSize m_SizeShowLabel;
	void InitWindow();
	void virtualPress(QKeyEvent * event);

	//label_show原始图
	cv::Mat m_MatLiveImg;
	cv::Rect m_RectOpencv;
	//label_show是否有图
	bool m_bshowImg;
	//鼠标按下标识符
	bool m_bButton;
	QPoint m_PointOriginal;
	QRect m_RectToDraw;

	public slots:
	//重写
	//void keyPressEvent(QKeyEvent * event);
	//void keyReleaseEvent(QKeyEvent * event);
	bool eventFilter(QObject *watched, QEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
		//槽函数
	void onStartPlay();
	void onOpen();
	void onClose();
	void onConvertPlay();
	void onShowImage(Mat);
};
