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
	//��ǰ����ͼ�����
	int m_isaveImageindex;
	void GetNextImageIndex();
	//����·��
	QString m_SvideoPath;
	//�ж��Ƿ�Ϊ��Ƶ����
	//0:��Ƶ 1:ͼ���ļ��� 2:��ͼ
	int m_iIsWhat;
	//��ͣ����
	bool m_Pause;
	//ȷ�����Ƿ����
	bool m_bContinue;
	//Tools����Ŀ¼
	QString AppPath;
	//���߳�ʵ��
	MultPlay *m_Play;
	//���߳̽���
	QThread *m_PlayThread;
	QLabel *m_LabelShow;
	QSize m_SizeShowLabel;
	//�Ҽ��˵�
	void ShowPopWindow(QPoint point);
	void InitWindow();
	void virtualPress(QKeyEvent * event);
	//��ʼ���Ѵ��ڵ�ģ���ļ�
	QList<DefineSave> SaveModel;
	void IntiCheckList();
	void SaveCheckList();
	bool m_bModelChange;


	QStringList m_qslImageList;
	void GetImageList();
	void UpdateLabelList(QString str);

	//label_showԭʼͼ
	cv::Mat m_MatLiveImg;
	cv::Rect m_RectOpencv;
	//label_show�Ƿ���ͼ
	bool m_bshowImg;
	//��갴�±�ʶ��
	bool m_bButton;
	QPoint m_PointOriginal;
	QRect m_RectToDraw;
	QRect m_OriRect;
	public slots:
	//��д
	//void keyPressEvent(QKeyEvent * event);
	//void keyReleaseEvent(QKeyEvent * event);
	bool eventFilter(QObject *watched, QEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
		//�ۺ���
	void onChangeListItem(QListWidgetItem *,QListWidgetItem *);
	void closeEvent(QCloseEvent *event);
	void onStartPlay();
	void onOpen();
	void onClose();
	void onConvertPlay();
	void onShowImage(Mat);
	void onCreateModel(QString modelname,int sampleindex);
};
