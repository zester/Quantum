/********************************************************************************
** Form generated from reading UI file 'mainDialog.ui'
**
** Created: Sun Sep 4 07:30:55 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "rosterListView.h"
#include "searchLineEdit.h"
#include "signInStatusLabel.h"

QT_BEGIN_NAMESPACE

class Ui_mainDialogClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    searchLineEdit *lineEdit_filter;
    rosterListView *listView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_addContact;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_settings;
    QWidget *page_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLineEdit *lineEdit_userName;
    QLineEdit *lineEdit_password;
    QCheckBox *checkBox_rememberPasswd;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_signIn;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    signInStatusLabel *label_status;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QLabel *label_throbber;
    QLabel *label;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *mainDialogClass)
    {
        if (mainDialogClass->objectName().isEmpty())
            mainDialogClass->setObjectName(QString::fromUtf8("mainDialogClass"));
        mainDialogClass->setEnabled(true);
        mainDialogClass->resize(236, 484);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/resource/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainDialogClass->setWindowIcon(icon);
        verticalLayout_4 = new QVBoxLayout(mainDialogClass);
        verticalLayout_4->setContentsMargins(6, 6, 6, 6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        stackedWidget = new QStackedWidget(mainDialogClass);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 4, 0, 0);
        lineEdit_filter = new searchLineEdit(page);
        lineEdit_filter->setObjectName(QString::fromUtf8("lineEdit_filter"));
        lineEdit_filter->setEnabled(true);

        verticalLayout_3->addWidget(lineEdit_filter);

        listView = new rosterListView(page);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        verticalLayout_3->addWidget(listView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_addContact = new QPushButton(page);
        pushButton_addContact->setObjectName(QString::fromUtf8("pushButton_addContact"));
        pushButton_addContact->setMinimumSize(QSize(29, 29));
        pushButton_addContact->setMaximumSize(QSize(29, 29));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/resource/addButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addContact->setIcon(icon1);
        pushButton_addContact->setIconSize(QSize(29, 29));

        horizontalLayout_3->addWidget(pushButton_addContact);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_settings = new QPushButton(page);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));
        pushButton_settings->setMinimumSize(QSize(29, 29));
        pushButton_settings->setMaximumSize(QSize(29, 29));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/resource/settingsButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_settings->setIcon(icon2);
        pushButton_settings->setIconSize(QSize(29, 29));
        pushButton_settings->setDefault(true);

        horizontalLayout_3->addWidget(pushButton_settings);


        verticalLayout_3->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout = new QVBoxLayout(page_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, -1, 20, -1);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit_userName = new QLineEdit(page_2);
        lineEdit_userName->setObjectName(QString::fromUtf8("lineEdit_userName"));

        verticalLayout->addWidget(lineEdit_userName);

        lineEdit_password = new QLineEdit(page_2);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_password);

        checkBox_rememberPasswd = new QCheckBox(page_2);
        checkBox_rememberPasswd->setObjectName(QString::fromUtf8("checkBox_rememberPasswd"));

        verticalLayout->addWidget(checkBox_rememberPasswd);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_signIn = new QPushButton(page_2);
        pushButton_signIn->setObjectName(QString::fromUtf8("pushButton_signIn"));

        horizontalLayout_2->addWidget(pushButton_signIn);

        pushButton_cancel = new QPushButton(page_2);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_2->addWidget(pushButton_cancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_status = new signInStatusLabel(page_2);
        label_status->setObjectName(QString::fromUtf8("label_status"));

        horizontalLayout_4->addWidget(label_status);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        label_throbber = new QLabel(page_2);
        label_throbber->setObjectName(QString::fromUtf8("label_throbber"));

        horizontalLayout->addWidget(label_throbber);

        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(label);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        stackedWidget->addWidget(page_2);

        verticalLayout_4->addWidget(stackedWidget);


        retranslateUi(mainDialogClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainDialogClass);
    } // setupUi

    void retranslateUi(QDialog *mainDialogClass)
    {
        mainDialogClass->setWindowTitle(QApplication::translate("mainDialogClass", "QXmpp", 0, QApplication::UnicodeUTF8));
        pushButton_addContact->setText(QString());
        pushButton_settings->setText(QString());
        label_3->setText(QApplication::translate("mainDialogClass", "Login:", 0, QApplication::UnicodeUTF8));
        lineEdit_userName->setText(QString());
        lineEdit_password->setText(QString());
        checkBox_rememberPasswd->setText(QApplication::translate("mainDialogClass", "Remember password", 0, QApplication::UnicodeUTF8));
        pushButton_signIn->setText(QApplication::translate("mainDialogClass", "Sign in", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("mainDialogClass", "Cancel", 0, QApplication::UnicodeUTF8));
        label_status->setText(QString());
        label_2->setText(QString());
        label_throbber->setText(QApplication::translate("mainDialogClass", "movie", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainDialogClass: public Ui_mainDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
