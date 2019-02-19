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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtModelCreateClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_show;
    QListWidget *imagelist;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtModelCreateClass)
    {
        if (QtModelCreateClass->objectName().isEmpty())
            QtModelCreateClass->setObjectName(QStringLiteral("QtModelCreateClass"));
        QtModelCreateClass->resize(1070, 722);
        QtModelCreateClass->setMouseTracking(true);
        centralWidget = new QWidget(QtModelCreateClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_show = new QLabel(centralWidget);
        label_show->setObjectName(QStringLiteral("label_show"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_show->sizePolicy().hasHeightForWidth());
        label_show->setSizePolicy(sizePolicy);
        label_show->setMouseTracking(true);
        label_show->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label_show, 0, 0, 2, 1);

        imagelist = new QListWidget(centralWidget);
        imagelist->setObjectName(QStringLiteral("imagelist"));
        imagelist->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(imagelist, 0, 1, 2, 1);

        QtModelCreateClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtModelCreateClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1070, 23));
        QtModelCreateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtModelCreateClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtModelCreateClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtModelCreateClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtModelCreateClass->setStatusBar(statusBar);

        retranslateUi(QtModelCreateClass);

        QMetaObject::connectSlotsByName(QtModelCreateClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtModelCreateClass)
    {
        QtModelCreateClass->setWindowTitle(QApplication::translate("QtModelCreateClass", "QtModelCreate", nullptr));
        label_show->setText(QApplication::translate("QtModelCreateClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtModelCreateClass: public Ui_QtModelCreateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMODELCREATE_H
