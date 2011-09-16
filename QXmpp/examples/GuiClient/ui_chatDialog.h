/********************************************************************************
** Form generated from reading UI file 'chatDialog.ui'
**
** Created: Sun Sep 4 07:30:55 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatDialogClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLineEdit *lineEdit;
    QWidget *widget_2;

    void setupUi(QDialog *chatDialogClass)
    {
        if (chatDialogClass->objectName().isEmpty())
            chatDialogClass->setObjectName(QString::fromUtf8("chatDialogClass"));
        chatDialogClass->resize(445, 291);
        chatDialogClass->setMinimumSize(QSize(445, 0));
        verticalLayout = new QVBoxLayout(chatDialogClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(chatDialogClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget);

        lineEdit = new QLineEdit(chatDialogClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 50));
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(lineEdit);

        widget_2 = new QWidget(chatDialogClass);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(chatDialogClass);

        QMetaObject::connectSlotsByName(chatDialogClass);
    } // setupUi

    void retranslateUi(QDialog *chatDialogClass)
    {
        chatDialogClass->setWindowTitle(QApplication::translate("chatDialogClass", "Dialog", 0, QApplication::UnicodeUTF8));
        chatDialogClass->setStyleSheet(QApplication::translate("chatDialogClass", "alternate-background-color: rgb(255, 255, 255);", 0, QApplication::UnicodeUTF8));
        widget->setStyleSheet(QApplication::translate("chatDialogClass", "background-color: rgb(255, 255, 255);", 0, QApplication::UnicodeUTF8));
        widget_2->setStyleSheet(QApplication::translate("chatDialogClass", "background-color: rgb(255, 255, 255);", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chatDialogClass: public Ui_chatDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
