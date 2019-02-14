#include "QtPoPWindow.h"

QtPoPWindow::QtPoPWindow(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QString AppPath = qApp->applicationDirPath();
	QFile file(AppPath + "/predefined_classes.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("配置错误"), QString::fromLocal8Bit("未找到predefined_classes文件"));
	}
	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QString str(line);
		m_listClass.append(str);
	}
	file.close();
	QStandardItemModel *ItemModel = new QStandardItemModel(this);
//	int nCount = m_listClass.size();
// 	for (int i = 0; i < nCount; i++)
// 	{
// 		//QString string = static_cast<QString>(m_listClass.at(i));
// 		//QStandardItem *item = new QStandardItem(string);
// 		//ItemModel->appendRow(item);
// 		ui.ClassList->add
// 	}
	ui.ClassList->addItems(m_listClass);
	connect(ui.ClassList, SIGNAL(clicked(QModelIndex)), this, SLOT(SelectSimple(QModelIndex)));
}

QtPoPWindow::~QtPoPWindow()
{
}

void QtPoPWindow::SaveParam()
{
	QString AppPath = qApp->applicationDirPath();
	QFile file(AppPath + "/predefined_classes.txt");
	if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("配置错误"), QString::fromLocal8Bit("未找到predefined_classes文件"));
	}
	file.close();
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("配置错误"), QString::fromLocal8Bit("未找到predefined_classes文件"));
	}
	QTextStream in(&file);
	int nCount = m_listClass.size();
	for (int i=0;i<nCount;i++)
	{
		in << m_listClass [i];
	}
	//in << *(m_listClass.end() - 1);

	file.close();
}

void QtPoPWindow::accept()
{
	bool b_repeat = false;
	m_sResult = ui.ClassName->toPlainText();
	int nCount = ui.ClassList->count();
	for (int j = 0; j < nCount; j++)
	{
		QString itemPath = ui.ClassList->item(j)->text();
		if (itemPath == m_sResult)
		{
			b_repeat = true;
			break;
		}
	}
	if (!b_repeat)
	{
		//没有重复的需要保存
		if (QMessageBox::Save == QMessageBox::question(nullptr, QString::fromLocal8Bit("无样本名称"), QString::fromLocal8Bit("是否保存新名称：\r\n") + m_sResult), QMessageBox::Save, QMessageBox::Cancel)
		{
			//if (==)
			//{
			//}
			if ((*(m_listClass.end() - 1)).right(1) !="\n")
			{
				(*(m_listClass.end() - 1)) += "\n";
			}
			m_listClass.push_back(m_sResult);
			SaveParam();
		}
	}
}

void QtPoPWindow::SelectSimple(QModelIndex index)
{
	QString strTemp = index.data().toString();
	ui.ClassName->setText(strTemp);
	return;
}