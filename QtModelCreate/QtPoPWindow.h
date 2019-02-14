#pragma once

#include <QDialog>
#include "AllRelay.h"
#include "ui_QtPoPWindow.h"

class QtPoPWindow : public QDialog
{
	Q_OBJECT

public:
	QtPoPWindow(QDialog *parent = Q_NULLPTR);
	~QtPoPWindow();
	QString m_sResult;
private:
	Ui::QtPoPWindow ui;
	QStringList m_listClass;
	void SaveParam();
	public slots:
	void SelectSimple(QModelIndex);
	void accept();
};
