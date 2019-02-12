/********************************************************************************
** Form generated from reading UI file 'QtModelCreate.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMODELCREATE_H
#define UI_QTMODELCREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtModelCreateClass
{
public:
    QWidget *centralWidget;
    QLabel *label_show;
    QPushButton *pb_Start;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtModelCreateClass)
    {
        if (QtModelCreateClass->objectName().isEmpty())
            QtModelCreateClass->setObjectName(QStringLiteral("QtModelCreateClass"));
        QtModelCreateClass->resize(938, 722);
        QtModelCreateClass->setMouseTracking(true);
        centralWidget = new QWidget(QtModelCreateClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        label_show = new QLabel(centralWidget);
        label_show->setObjectName(QStringLiteral("label_show"));
        label_show->setGeometry(QRect(10, 0, 801, 651));
        label_show->setMouseTracking(true);
        label_show->setFrameShape(QFrame::Box);
        pb_Start = new QPushButton(centralWidget);
        pb_Start->setObjectName(QStringLiteral("pb_Start"));
        pb_Start->setGeometry(QRect(840, 10, 75, 23));
        QtModelCreateClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtModelCreateClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 938, 23));
        QtModelCreateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtModelCreateClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtModelCreateClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtModelCreateClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtModelCreateClass->setStatusBar(statusBar);

        retranslateUi(QtModelCreateClass);
        QObject::connect(pb_Start, SIGNAL(clicked()), QtModelCreateClass, SLOT(onStartPlay()));

        QMetaObject::connectSlotsByName(QtModelCreateClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtModelCreateClass)
    {
        QtModelCreateClass->setWindowTitle(QApplication::translate("QtModelCreateClass", "QtModelCreate", nullptr));
        label_show->setText(QApplication::translate("QtModelCreateClass", "TextLabel", nullptr));
        pb_Start->setText(QApplication::translate("QtModelCreateClass", "\346\222\255\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtModelCreateClass: public Ui_QtModelCreateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMODELCREATE_H
