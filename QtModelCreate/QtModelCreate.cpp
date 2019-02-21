#include "QtModelCreate.h"

QtModelCreate::QtModelCreate(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_iIsWhat = -1;
	m_SvideoPath = "";
	m_bButton = false;
	m_bshowImg = false;
	m_Pause = true;
	m_bContinue = false;
	m_bModelChange = false;
	m_isaveImageindex = -1;
	AppPath = qApp->applicationDirPath();
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
	//UpdateLabelList("SS");
}

void QtModelCreate::GetNextImageIndex()
{
	QString dir_str = AppPath + "/JPEGImages/";
	QDir dir(dir_str);
	QStringList filter;
	filter << "*.jpg";
	dir.setNameFilters(filter);
	QStringList fileInfoList = dir.entryList(filter);
	m_isaveImageindex = fileInfoList.size();
}

void QtModelCreate::ShowPopWindow(QPoint point)
{
	QtPoPWindow dlg;
	dlg.move(point);
	QObject::connect(&dlg, SIGNAL(Signal_CreateModel(QString, int)), this, SLOT(onCreateModel(QString, int)));
	int result = dlg.exec();
	if (QDialog::Accepted == result)
	{
		if (true == m_bContinue)
		{
			//若未暂停视频，点击OK则继续播放
			emit Signal_ConvertPlay();

			QString dir_str = AppPath + "/JPEGImages/";
			QDir dir;
			if (!dir.exists(dir_str))
			{
				bool res = dir.mkdir(dir_str);
				if (!res)
				{
					QMessageBox::warning(nullptr, QString::fromLocal8Bit("创建文件夹警告"), QString::fromLocal8Bit("模板创建失败"));
					return;
				}
			}
			GetNextImageIndex();
		}
	}
}

void QtModelCreate::InitWindow()
{
	QMenu* pMenuA = new QMenu(QString::fromLocal8Bit("文件"));
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

	//ui.pb_Start->installEventFilter(this);
	//ui.imagelist->installEventFilter(this);
	ui.labellist->installEventFilter(this);
	bool flag = QObject::connect(ui.imagelist, SIGNAL(currentItemChanged(QListWidgetItem *,QListWidgetItem *)), this, SLOT(onChangeListItem(QListWidgetItem *,QListWidgetItem *)));
	flag = QObject::connect(ui.imagelist, SIGNAL(DefineMouseMove(QMouseEvent*)), this, SLOT(mouseMoveEvent(QMouseEvent*)));

}
bool QtModelCreate::eventFilter(QObject * watched, QEvent * event)
{
	//if (watched == ui.pb_Start)
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
		if (m_LabelShow->geometry().contains(m_LabelShow->mapFromGlobal(poi)))
		{
			setCursor(Qt::CrossCursor);
			if (m_bButton)
			{
				QRect rec = m_LabelShow->geometry();
				QPoint pt = m_LabelShow->mapFromGlobal(poi);
				pt.setX(pt.x() /*- rec.x() */ - m_LabelShow->frameWidth());
				pt.setY(pt.y() /*- rec.y() */ - m_LabelShow->frameWidth());
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
				m_OriRect = QRect(m_RectOpencv.x, m_RectOpencv.y, m_RectOpencv.width, m_RectOpencv.height);
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
	if (ui.label_show->geometry().contains(m_LabelShow->mapFromGlobal(QCursor::pos())))
	{
		if (m_bshowImg)
		{
			if (event->button() == Qt::LeftButton)
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
			if (event->button() == Qt::RightButton)
			{
				ShowPopWindow(QCursor::pos());
			}
		}
	}
}
void QtModelCreate::mouseReleaseEvent(QMouseEvent * event)
{
	{
		if (m_bshowImg)
		{
			m_bButton = false;
		}
	}
}
void QtModelCreate::onChangeListItem(QListWidgetItem * current, QListWidgetItem *previous)
{
	QString path = m_SvideoPath + current->text();
	Mat img = imread(path.toStdString().c_str());
	onShowImage(img);
	UpdateLabelList(current->text());
}
void QtModelCreate::closeEvent(QCloseEvent * event)
{
	SaveCheckList();
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
		GetNextImageIndex();
		m_bContinue = false;
		break;
	}
	case Qt::Key_Z:
	{
		ui.imagelist->setCurrentRow(ui.imagelist->currentRow() - 1<0?0: ui.imagelist->currentRow() - 1);
		break;
	}
	case Qt::Key_C:
	{
		ui.imagelist->setCurrentRow(ui.imagelist->currentRow() + 1>=ui.imagelist->count() ? ui.imagelist->count()-1 : ui.imagelist->currentRow() + 1);
		break;
	}
	case Qt::Key_S:
		break;
	default:
		break;
	}
	event->ignore();
}
void QtModelCreate::IntiCheckList()
{
	QFile file(AppPath + "/test.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("配置错误"), QString::fromLocal8Bit("未找到predefined_classes文件"));
	}
	QString str;
	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		str = line;
		int startindex = str.lastIndexOf("/") + 1;
		int endindex = str.lastIndexOf(".jpg") + 4;
		QString name = str.mid(startindex, endindex + 1 - startindex);
		QString strrect = str.right(str.length()-endindex - 1);
		strrect = strrect.trimmed();
		strrect.replace(" ", ",");
		QStringList listRect = strrect.split(QRegExp("[,*/^]"), QString::SkipEmptyParts);
		if (0 != listRect.size() % 5)
		{
			QMessageBox::warning(nullptr, QString::fromLocal8Bit("严重错误！"), QString("test.txt") + QString::fromLocal8Bit("格式错误"));
			return;
		}
		int nRectCount = listRect.size() / 5;
		int indexRect = 0;
		DefineSave rectandsimple;
		rectandsimple.path = str.left(str.lastIndexOf(".jpg") + 4);
		rectandsimple.name = name.trimmed();

		while (indexRect < nRectCount)
		{
			rectandsimple.ImgObject.append(
				QRect(listRect[indexRect * 5 + 0].toInt(),
					listRect[indexRect * 5 + 1].toInt(),
					listRect[indexRect * 5 + 2].toInt(),
					listRect[indexRect * 5 + 3].toInt()));
			rectandsimple.ImgObjectSample.append(listRect[indexRect * 5 + 4].toInt());
			indexRect++;
		}
		SaveModel.append(rectandsimple);
	}

	if (m_iIsWhat==1)
		m_SvideoPath = AppPath +"/"+ str.left(str.lastIndexOf("/") );
	if (m_iIsWhat==0)
	{
		//保存图像序号
		QString dir_str = AppPath + "/JPEGImages/";
		QDir dir;
		if (!dir.exists(dir_str))
		{
			bool res = dir.mkdir(dir_str);
			if (!res)
			{
				QMessageBox::warning(nullptr, QString::fromLocal8Bit("创建文件夹警告"), QString::fromLocal8Bit("模板创建失败"));
				return;
			}
		}
	}
	GetNextImageIndex();
}
void QtModelCreate::SaveCheckList()
{
	QFile file(AppPath + "/test.txt");
	if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("配置错误"), QString::fromLocal8Bit("未找到predefined_classes文件"));
	}

	QTextStream in(&file);
	QList<DefineSave>::iterator it_end = SaveModel.end();
	for (QList<DefineSave>::iterator it = SaveModel.begin();it!= it_end;it++)
	{
		if ((*it).ImgObject.size()!= (*it).ImgObject.size())
		{
			QMessageBox::warning(nullptr, QString::fromLocal8Bit("模板创建错误"), QString::fromLocal8Bit("模板框与模板类数据不符")+(*it).name);
			continue;
		}
		QString str_sample = " ";
		for (int i = 0;i < (*it).ImgObject.size();i++)
		{
			str_sample +=
				QString::number((*it).ImgObject[i].x()) + "," +
				QString::number((*it).ImgObject[i].y()) + "," +
				QString::number((*it).ImgObject[i].width()) + "," +
				QString::number((*it).ImgObject[i].height()) + "," + 
				QString::number((*it).ImgObjectSample[i]) + " ";
		}

		in << it->path + str_sample << endl;
	}

}
void QtModelCreate::GetImageList()
{
	if (1 == m_iIsWhat)
	{
		QDir prober(m_SvideoPath);
		QStringList filter;
		filter << "*.jpg";
		prober.setNameFilters(filter);
		m_qslImageList = prober.entryList(filter);
		if (m_qslImageList.size()<=0)
		{
			QMessageBox::warning(nullptr, QString::fromLocal8Bit("读取目录存在异常"), QString::fromLocal8Bit("目录中未找到JPG图片"));
			m_iIsWhat = -1;
			m_SvideoPath = "";
			return;
		}
		else
		{
			ui.imagelist->addItems(m_qslImageList);

		}
	}
}
void QtModelCreate::UpdateLabelList(QString str)
{
	ui.labellist->clear();
	QStringList _listClass;
	QFile file(AppPath + "/predefined_classes.txt");

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("配置错误"), QString::fromLocal8Bit("未找到predefined_classes文件"));
	}
	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QString str(line);
		_listClass.append(str);
	}
	file.close();
	size_t ncount = SaveModel.size();
	for (size_t i = 0;i < ncount;i++)
	{
		if (str == SaveModel[i].name)
		{
			m_SelectedDefineSave = SaveModel[i];
			break;
		}
	}

	for (int i=0;i<m_SelectedDefineSave.ImgObjectSample.size();i++)
	{
		QListWidgetItem * item = new QListWidgetItem(ui.labellist);
		QCheckBox * box = new QCheckBox(ui.labellist);
		box->setCheckable(true);
		QFont fon = box->font();
		fon.setPointSize(11);
		box->setFont(fon);
		box->installEventFilter(this);
		ui.labellist->addItem(item);
		ui.labellist->setItemWidget(item, box);
		box->setText(_listClass[m_SelectedDefineSave.ImgObjectSample[i]]);
	}
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
	cv::resize(image, image, Size(m_LabelShow->width(), m_LabelShow->height()));
	cvtColor(image, image, CV_BGR2RGB);
	QImage disImage = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.step, QImage::Format_RGB888);
	m_LabelShow->setPixmap(QPixmap::fromImage(disImage));
	m_bshowImg = true;
}
void QtModelCreate::onCreateModel(QString modelname, int sampleindex)
{
	if ("\n" == modelname.right(1))
	{
		modelname = modelname.left(modelname.length() - 1);
	}

	QString dir_str = AppPath + "/JPEGImages/";
	QString str;
	str.sprintf("%05d", m_isaveImageindex);
	QString path = dir_str + str + ".jpg";
	imwrite(path.toStdString(), m_MatLiveImg);

	int nCount = SaveModel.size();
	bool b_repeat = false;
	for (size_t i = 0;i < nCount;i++)
	{
		if (str + ".jpg" == SaveModel[i].name)
		{
			b_repeat = true;
			SaveModel[i].ImgObject.append(m_OriRect);
			SaveModel[i].ImgObjectSample.append(sampleindex);
			break;
		}
	}
	if (!b_repeat)
	{
		DefineSave rectandsimple;
		rectandsimple.path = "/JPEGImages/" + str + ".jpg";
		rectandsimple.name = str + ".jpg";
		rectandsimple.ImgObject.append(m_OriRect);
		rectandsimple.ImgObjectSample.append(sampleindex);
		SaveModel.append(rectandsimple);
	}
}
void QtModelCreate::onOpen()
{
	//获取发送消息
	QAction *pAvt = qobject_cast<QAction*>(sender());
	if ("OpenVideo" == pAvt->text())
	{
		m_SvideoPath = QFileDialog::getOpenFileName(this, tr("Find Files"), QDir::currentPath(), QString::fromLocal8Bit("视频文件(*.mp4;*.avi);;所有文件(*.*)"));
		if (m_SvideoPath!="")
		{
			m_iIsWhat = 0;
		}
	}
	if ("OpenFile" == pAvt->text())
	{
		m_iIsWhat = 1;
		IntiCheckList();
		//m_SvideoPath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("打开文件夹"), QDir::currentPath());
		m_SvideoPath += "/";

		GetImageList();

	}
	if ("OpenImage" == pAvt->text())
	{
		m_SvideoPath = QFileDialog::getOpenFileName(this, tr("Find Files"), QDir::currentPath(), QString::fromLocal8Bit("图片文件(*.jpg;*.jpeg;*.bmp);;所有文件(*.*)"));
	}
	return;
}

