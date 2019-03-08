/********************************************************************************
** Form generated from reading UI file 'QtPoPWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPOPWINDOW_H
#define UI_QTPOPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtPoPWindow
{
public:
    QGridLayout *gridLayout;
    QListWidget *ClassList;
    QTextEdit *ClassName;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *QtPoPWindow)
    {
        if (QtPoPWindow->objectName().isEmpty())
            QtPoPWindow->setObjectName(QStringLiteral("QtPoPWindow"));
        QtPoPWindow->resize(325, 391);
        gridLayout = new QGridLayout(QtPoPWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ClassList = new QListWidget(QtPoPWindow);
        ClassList->setObjectName(QStringLiteral("ClassList"));

        gridLayout->addWidget(ClassList, 2, 0, 1, 1);

        ClassName = new QTextEdit(QtPoPWindow);
        ClassName->setObjectName(QStringLiteral("ClassName"));
        ClassName->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(ClassName, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(QtPoPWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(QtPoPWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), QtPoPWindow, SLOT(onOK()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QtPoPWindow, SLOT(reject()));
        QObject::connect(ClassList, SIGNAL(doubleClicked(QModelIndex)), QtPoPWindow, SLOT(onListDoubleClick()));

        QMetaObject::connectSlotsByName(QtPoPWindow);
    } // setupUi

    void retranslateUi(QWidget *QtPoPWindow)
    {
        QtPoPWindow->setWindowTitle(QApplication::translate("QtPoPWindow", "QtPoPWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtPoPWindow: public Ui_QtPoPWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPOPWINDOW_H
