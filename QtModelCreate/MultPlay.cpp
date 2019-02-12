#include "MultPlay.h"

MultPlay::MultPlay(QObject *parent, QLabel *labeltoshow)
	: QObject(parent)
{
// 	m_mPlayMutex = new QMutex();
// 	m_wPlayCondition = new QWaitCondition();
	m_showLabel = labeltoshow;
	m_Path = "";
}


MultPlay::~MultPlay()
{
}

void MultPlay::onPlayVideo()
{
	//��֤��Ƶ�ļ���ȷ
	if (""==m_Path)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("�ؼ�����"), QString::fromLocal8Bit("δ���ö�ȡĿ¼"));
		return;
	}
	QFileInfo prober(m_Path);
	if (!prober.isFile())
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("�ؼ�����"), QString::fromLocal8Bit("��Ƶ�ļ�����"));
		return;
	}
	if (prober.suffix() != "mp4"&& prober.suffix() != "avi")
	{
		return;
	}
	//��ȡ��Ƶ�ļ�
	VideoCapture capturer;
	capturer.open(m_Path.toStdString().c_str());

	Mat eachframes;
	bool b_readresult = capturer.read(eachframes);
	if (capturer.isOpened())
	{
		m_bLocked = false;
		while (b_readresult)
		{
			m_mPlayMutex.lock();
			b_readresult = capturer.read(eachframes);
			if (eachframes.empty()||eachframes.rows<=0|| eachframes.cols <= 0)
			{
				return;
			}
			else
			{
//				eachframes.copyTo(m_matTempImg);
				//cv::resize(eachframes, eachframes, Size(m_SizeShowLabel.width(), m_SizeShowLabel.height()));
				//cvtColor(eachframes, eachframes, CV_BGR2RGB);
				//QImage disImage = QImage((const unsigned char*)(eachframes.data), eachframes.cols, eachframes.rows, eachframes.step, QImage::Format_RGB888);
				emit Signal_ShowImage(eachframes);
				QThread::msleep(5);
			}

			m_mPlayMutex.unlock();
		}




	}


}

void MultPlay::onInitPath(QString str)
{
	m_Path = str;
	return;
}

void MultPlay::onPause()
{
	if (!m_bLocked)
	{
		m_mPlayMutex.lock();
		m_bLocked = !m_bLocked;
	}
	else
	{
		m_bLocked = !m_bLocked;
		m_mPlayMutex.unlock();
	}
	return;
}