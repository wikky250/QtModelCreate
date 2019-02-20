#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtModelCreate.h"
#include "AllRelay.h"
#include "MultPlay.h"
#include "QtPoPWindow.h"
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
	//当前保存图像序号
	int m_isaveImageindex;
	void GetNextImageIndex();
	//加载路径
	QString m_SvideoPath;
	//判断是否为视频加载
	//0:视频 1:图像文件夹 2:单图
	int m_iIsWhat;
	//暂停播放
	bool m_Pause;
	//确定后是否继续
	bool m_bContinue;
	//Tools所在目录
	QString AppPath;
	//多线程实例
	MultPlay *m_Play;
	//多线程进程
	QThread *m_PlayThread;
	QLabel *m_LabelShow;
	QSize m_SizeShowLabel;
	//右键菜单
	void ShowPopWindow(QPoint point);
	void InitWindow();
	void virtualPress(QKeyEvent * event);
	//初始化已存在的模板文件
	QList<DefineSave> SaveModel;
	void IntiCheckList();
	void SaveCheckList();
	bool m_bModelChange;


	QStringList m_qslImageList;
	void GetImageList();
	void UpdateLabelList(QString str);

	//label_show原始图
	cv::Mat m_MatLiveImg;
	cv::Rect m_RectOpencv;
	//label_show是否有图
	bool m_bshowImg;
	//鼠标按下标识符
	bool m_bButton;
	QPoint m_PointOriginal;
	QRect m_RectToDraw;
	QRect m_OriRect;
	public slots:
	//重写
	//void keyPressEvent(QKeyEvent * event);
	//void keyReleaseEvent(QKeyEvent * event);
	bool eventFilter(QObject *watched, QEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
		//槽函数
	void onChangeListItem(QListWidgetItem *,QListWidgetItem *);
	void closeEvent(QCloseEvent *event);
	void onStartPlay();
	void onOpen();
	void onClose();
	void onConvertPlay();
	void onShowImage(Mat);
	void onCreateModel(QString modelname,int sampleindex);
};
