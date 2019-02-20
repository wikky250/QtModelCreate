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
    QLabel *label;
    QLabel *label_show;
    QListWidget *labellist;
    QListWidget *imagelist;
    QLabel *label_2;
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
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 1, 1, 1);

        label_show = new QLabel(centralWidget);
        label_show->setObjectName(QStringLiteral("label_show"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_show->sizePolicy().hasHeightForWidth());
        label_show->setSizePolicy(sizePolicy);
        label_show->setMouseTracking(true);
        label_show->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label_show, 0, 0, 4, 1);

        labellist = new QListWidget(centralWidget);
        labellist->setObjectName(QStringLiteral("labellist"));
        labellist->setMaximumSize(QSize(200, 100));
        labellist->setMouseTracking(true);

        gridLayout->addWidget(labellist, 1, 1, 1, 1);

        imagelist = new QListWidget(centralWidget);
        imagelist->setObjectName(QStringLiteral("imagelist"));
        imagelist->setMaximumSize(QSize(200, 16777215));
        imagelist->setMouseTracking(true);

        gridLayout->addWidget(imagelist, 3, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

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
        label->setText(QApplication::translate("QtModelCreateClass", "\345\233\276\347\211\207\345\210\227\350\241\250", nullptr));
        label_show->setText(QApplication::translate("QtModelCreateClass", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("QtModelCreateClass", "\345\267\262\346\240\207\346\263\250\351\241\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtModelCreateClass: public Ui_QtModelCreateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMODELCREATE_H
