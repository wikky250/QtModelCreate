#pragma once

#include <QDialog>
#include "AllRelay.h"
#include "ui_QtPoPWindow.h"

class QtPoPWindow : public QDialog
{
	Q_OBJECT
		signals:
	void Signal_CreateModel(QString);
public:
	QtPoPWindow(QDialog *parent = Q_NULLPTR);
	~QtPoPWindow();
	QString m_sResult;
private:
	Ui::QtPoPWindow ui;
	QStringList m_listClass;
	QModelIndex m_selectedindex;
	void SaveParam();
	public slots:
	void SelectSimple(QModelIndex);
	void onOK();
	void reject();

	bool eventFilter(QObject *watched, QEvent *event);
};
