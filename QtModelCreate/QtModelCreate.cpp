#include "QtModelCreate.h"

QtModelCreate::QtModelCreate(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_BisVideo = false;
	m_SvideoPath = "";
	m_bButton = false;
	m_bshowImg = false;
	m_Pause = true;
	m_bContinue = false;
	InitWindow();
	QObject::connect(this, SIGNAL(Signal_ConvertPlay()), this, SLOT(onConvertPlay()));
	m_LabelShow = this->findChild<QLabel *>("label_show");
	int zz = m_LabelShow->frameWidth();
	m_SizeShowLabel = m_LabelShow->size();
	m_SizeShowLabel.setWidth(m_SizeShowLabel.width() - zz * 2);
	m_SizeShowLabel.setHeight(m_SizeShowLabel.height() - zz * 2);
	m_Play = new MultPlay(nullptr, m_LabelShow);
	QObject::connect(this, SIGNAL(Signal_Play()), m_Play, SLOT(onPlayVideo()));
	QObject::connect(m_Play, SIGNAL(Signal_ShowImage(Mat)), this, SLOT(onShowImage(Mat)), Qt::DirectConnection);
	QObject::connect(this, SIGNAL(Signal_ConverttoPlay()), m_Play, SLOT(onPause()), Qt::DirectConnection);
	m_PlayThread = new QThread();
	m_Play->moveToThread(m_PlayThread);
	m_PlayThread->start();
	setMouseTracking(true);
	ui.centralWidget->setMouseTracking(true);
	m_LabelShow->setMouseTracking(true);
}

void QtModelCreate::ShowPopWindow(QPoint point)
{
	QtPoPWindow dlg;
	dlg.move(point);
	QObject::connect(&dlg, SIGNAL(Signal_CreateModel(QString)), this, SLOT(onCreateModel(QString)));
	int result = dlg.exec();
	if (QDialog::Accepted==result)
	{
		if (true == m_bContinue)
		{
			//��δ��ͣ��Ƶ�����OK���������
			emit Signal_ConvertPlay();
		}

	}
	else
	{

	}
}

void QtModelCreate::InitWindow()
{
	QMenu* pMenuA = new QMenu(QString::fromLocal8Bit("�ļ�"));
	QAction * MenuButton;
	MenuButton = new QAction("OpenVideo", this);
	MenuButton->setStatusTip("you will open a video");
	QObject::connect(MenuButton, SIGNAL(triggered()), this, SLOT(onOpen()));
	pMenuA->addAction(MenuButton);

	MenuButton = new QAction("OpenFile", this);
	MenuButton->setStatusTip("you will open a ImageFile");
	QObject::connect(MenuButton, SIGNAL(triggered()), this, SLOT(onOpen()));
	pMenuA->addAction(MenuButton);

	MenuButton = new QAction("OpenImage", this);
	MenuButton->setStatusTip("you will open a image");
	QObject::connect(MenuButton, SIGNAL(triggered()), this, SLOT(onOpen()));
	pMenuA->addAction(MenuButton);


	pMenuA->addSeparator();
	MenuButton = new QAction("Close", this);
	MenuButton->setStatusTip("Close execution");
	QObject::connect(MenuButton, SIGNAL(triggered()), this, SLOT(onClose()));
	pMenuA->addAction(MenuButton);


	QMenuBar* pMenuBar = ui.menuBar;
	pMenuBar->addMenu(pMenuA);

	ui.pb_Start->installEventFilter(this);


}
bool QtModelCreate::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == ui.pb_Start)
	{
		if (event->type() == QEvent::KeyRelease)
		{
			virtualPress(static_cast<QKeyEvent *>(event));
			return true;
		}
	}
	if (event->type() == QEvent::MouseMove) {
		return false;
	}
	return false;
}
void QtModelCreate::mouseMoveEvent(QMouseEvent * event)
{

	QPoint poi = QCursor::pos();
	if (m_bshowImg)
	{
		if (m_LabelShow->geometry().contains(this->mapFromGlobal(poi)))
		{
			setCursor(Qt::CrossCursor);
			if (m_bButton)
			{
				QRect rec = m_LabelShow->geometry();
				QPoint pt = m_LabelShow->mapFromGlobal(poi);
				pt.setX(pt.x() /*- rec.x() */- m_LabelShow->frameWidth());
				pt.setY(pt.y() /*- rec.y() */- m_LabelShow->frameWidth());
				double scale_x = m_MatLiveImg.cols*1.0 / (rec.width() - m_LabelShow->frameWidth() * 2);
				double scale_y = m_MatLiveImg.rows*1.0 / (rec.height() - m_LabelShow->frameWidth() * 2);
				if (pt.x() > m_PointOriginal.x())
				{
					m_RectToDraw.setLeft(m_PointOriginal.x());
					m_RectToDraw.setRight(pt.x());
				}
				else
				{
					m_RectToDraw.setRight(m_PointOriginal.x());
					m_RectToDraw.setLeft(pt.x());
				}
				if (pt.y() > m_PointOriginal.y())
				{
					m_RectToDraw.setTop(m_PointOriginal.y());
					m_RectToDraw.setBottom(pt.y());
				}
				else
				{
					m_RectToDraw.setBottom(m_PointOriginal.y());
					m_RectToDraw.setTop(pt.y());
				}
				cv::Mat img2show;
				cvtColor(m_MatLiveImg, img2show, CV_BGR2RGB);
				m_RectOpencv = cv::Rect(m_RectToDraw.x()*scale_x, m_RectToDraw.y()*scale_y, m_RectToDraw.width()*scale_x, m_RectToDraw.height()*scale_y);
				cv::rectangle(img2show, m_RectOpencv, cv::Scalar(255, 0, 0), 5, 8, 0);
				cv::resize(img2show, img2show, Size(m_LabelShow->width(), m_LabelShow->height()));
				QImage disImage = QImage((const unsigned char*)(img2show.data), img2show.cols, img2show.rows, img2show.step, QImage::Format_RGB888);
				m_LabelShow->setPixmap(QPixmap::fromImage(disImage));
			}
		}
		else
			setCursor(Qt::ArrowCursor);
	}
	else
		setCursor(Qt::ArrowCursor);

	return;
}
void QtModelCreate::mousePressEvent(QMouseEvent * event)
{
	if (ui.label_show->geometry().contains(this->mapFromGlobal(QCursor::pos())) && event->button() == Qt::LeftButton)
	{
		if (m_bshowImg)
		{
			QRect rec = m_LabelShow->geometry();
			m_PointOriginal = m_LabelShow->mapFromGlobal(QCursor::pos());
			m_PointOriginal.setX(m_PointOriginal.x() /*- rec.x()*/ - m_LabelShow->frameWidth());
			m_PointOriginal.setY(m_PointOriginal.y() /*- rec.y()*/ - m_LabelShow->frameWidth());
			m_bButton = true;
			if (true == m_Pause)
			{
				emit Signal_ConvertPlay();
				m_bContinue = true;
			}
		}
	}
}
void QtModelCreate::mouseReleaseEvent(QMouseEvent * event)
{
	if (ui.label_show->geometry().contains(this->mapFromGlobal(QCursor::pos())) && event->button() == Qt::LeftButton)
	{
		if (m_bshowImg)
		{
			ShowPopWindow(QCursor::pos());
		}
	}
	m_bButton = false;
}
void QtModelCreate::onStartPlay()
{
	if ("" == m_SvideoPath)
	{
		return;
	}
	m_Play->onInitPath(m_SvideoPath);
	emit Signal_Play();
}
void QtModelCreate::onClose()
{
	this->close();
}
void QtModelCreate::virtualPress(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Space:
	{
		emit Signal_ConvertPlay();
		m_bContinue = false;
		break;
	}
	case Qt::Key_Z:
		break;
	case Qt::Key_X:
		break;
	case Qt::Key_S:
		break;
	default:
		break;
	}
	event->ignore();
}
void QtModelCreate::onConvertPlay()
{
	m_Pause = !m_Pause;
	emit Signal_ConverttoPlay();
	return;
}
void QtModelCreate::onShowImage(Mat image)
{
	image.copyTo(m_MatLiveImg);
	cv::resize(image, image, Size(m_LabelShow->width(),m_LabelShow->height()));
	cvtColor(image, image, CV_BGR2RGB);
	QImage disImage = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.step, QImage::Format_RGB888);
	m_LabelShow->setPixmap(QPixmap::fromImage(disImage));
	m_bshowImg = true;
}
void QtModelCreate::onCreateModel(QString modelname)
{
	QMessageBox::about(nullptr, "", "");
}
void QtModelCreate::onOpen()
{
	//��ȡ������Ϣ
	QAction *pAvt = qobject_cast<QAction*>(sender());
	if ("OpenVideo" == pAvt->text())
	{
		m_SvideoPath = QFileDialog::getOpenFileName(this, tr("Find Files"), QDir::currentPath(), QString::fromLocal8Bit("��Ƶ�ļ�(*.mp4;*.avi);;�����ļ�(*.*)"));
		m_BisVideo = true;
	}
	if ("OpenFile" == pAvt->text())
	{
		m_SvideoPath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("���ļ���"), QDir::currentPath());
	}
	if ("OpenImage" == pAvt->text())
	{
		m_SvideoPath = QFileDialog::getOpenFileName(this, tr("Find Files"), QDir::currentPath(), QString::fromLocal8Bit("ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp);;�����ļ�(*.*)"));
	}
	return;
}
