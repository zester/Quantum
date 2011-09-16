/********************************************************************************
** Form generated from reading UI file 'statusWidget.ui'
**
** Created: Sun Sep 4 07:30:55 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWIDGET_H
#define UI_STATUSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "statusAvatarWidget.h"
#include "statusTextWidget.h"
#include "statusToolButton.h"

QT_BEGIN_NAMESPACE

class Ui_statusWidgetClass
{
public:
    QAction *actionBusy;
    QAction *actionAvailable;
    QAction *actionInvisible;
    QAction *actionSign_out;
    QAction *actionAway;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    statusToolButton *toolButton_userName;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    statusTextWidget *statusTextWidgetObject;
    QSpacerItem *horizontalSpacer_2;
    statusAvatarWidget *pushButton_avatar;

    void setupUi(QWidget *statusWidgetClass)
    {
        if (statusWidgetClass->objectName().isEmpty())
            statusWidgetClass->setObjectName(QString::fromUtf8("statusWidgetClass"));
        statusWidgetClass->resize(251, 40);
        actionBusy = new QAction(statusWidgetClass);
        actionBusy->setObjectName(QString::fromUtf8("actionBusy"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/resource/red.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBusy->setIcon(icon);
        actionAvailable = new QAction(statusWidgetClass);
        actionAvailable->setObjectName(QString::fromUtf8("actionAvailable"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/resource/green.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAvailable->setIcon(icon1);
        actionInvisible = new QAction(statusWidgetClass);
        actionInvisible->setObjectName(QString::fromUtf8("actionInvisible"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/resource/gray.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInvisible->setIcon(icon2);
        actionSign_out = new QAction(statusWidgetClass);
        actionSign_out->setObjectName(QString::fromUtf8("actionSign_out"));
        actionSign_out->setIcon(icon2);
        actionAway = new QAction(statusWidgetClass);
        actionAway->setObjectName(QString::fromUtf8("actionAway"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/resource/orange.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAway->setIcon(icon3);
        horizontalLayout_3 = new QHBoxLayout(statusWidgetClass);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(4, 0, 4, 0);
        label = new QLabel(statusWidgetClass);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/resource/green.png")));

        horizontalLayout_3->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton_userName = new statusToolButton(statusWidgetClass);
        toolButton_userName->setObjectName(QString::fromUtf8("toolButton_userName"));
        toolButton_userName->setPopupMode(QToolButton::InstantPopup);
        toolButton_userName->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_userName->setAutoRaise(true);
        toolButton_userName->setArrowType(Qt::DownArrow);

        horizontalLayout_2->addWidget(toolButton_userName);

        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        statusTextWidgetObject = new statusTextWidget(statusWidgetClass);
        statusTextWidgetObject->setObjectName(QString::fromUtf8("statusTextWidgetObject"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusTextWidgetObject->sizePolicy().hasHeightForWidth());
        statusTextWidgetObject->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(statusTextWidgetObject);

        horizontalSpacer_2 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        pushButton_avatar = new statusAvatarWidget(statusWidgetClass);
        pushButton_avatar->setObjectName(QString::fromUtf8("pushButton_avatar"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/resource/avatar.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_avatar->setIcon(icon4);
        pushButton_avatar->setIconSize(QSize(32, 32));

        horizontalLayout_3->addWidget(pushButton_avatar);


        retranslateUi(statusWidgetClass);

        QMetaObject::connectSlotsByName(statusWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *statusWidgetClass)
    {
        statusWidgetClass->setWindowTitle(QApplication::translate("statusWidgetClass", "Form", 0, QApplication::UnicodeUTF8));
        actionBusy->setText(QApplication::translate("statusWidgetClass", "Busy", 0, QApplication::UnicodeUTF8));
        actionAvailable->setText(QApplication::translate("statusWidgetClass", "Available", 0, QApplication::UnicodeUTF8));
        actionInvisible->setText(QApplication::translate("statusWidgetClass", "Invisible", 0, QApplication::UnicodeUTF8));
        actionSign_out->setText(QApplication::translate("statusWidgetClass", "Sign out", 0, QApplication::UnicodeUTF8));
        actionAway->setText(QApplication::translate("statusWidgetClass", "Away", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        toolButton_userName->setText(QApplication::translate("statusWidgetClass", "toolbutton", 0, QApplication::UnicodeUTF8));
        pushButton_avatar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class statusWidgetClass: public Ui_statusWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWIDGET_H
