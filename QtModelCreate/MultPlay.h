#pragma once

#include <QObject>
#include "AllRelay.h"



class MultPlay : public QObject
{
	Q_OBJECT
		signals:
	void Signal_ShowImage(Mat);
private:
	QString m_Path;
	QLabel* m_showLabel;
	bool m_bLocked;
public:
	QMutex m_mPlayMutex;
	QWaitCondition  m_wPlayCondition;
	MultPlay(QObject *parent, QLabel *labeltoshow);
	~MultPlay();
	public slots :
	void onInitPath(QString str);
	void onPause();
	void onPlayVideo();
};
