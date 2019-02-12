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
	//保证视频文件正确
	if (""==m_Path)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("关键错误！"), QString::fromLocal8Bit("未设置读取目录"));
		return;
	}
	QFileInfo prober(m_Path);
	if (!prober.isFile())
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("关键错误！"), QString::fromLocal8Bit("视频文件错误"));
		return;
	}
	if (prober.suffix() != "mp4"&& prober.suffix() != "avi")
	{
		return;
	}
	//读取视频文件
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