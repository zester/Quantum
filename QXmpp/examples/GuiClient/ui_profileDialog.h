/********************************************************************************
** Form generated from reading UI file 'profileDialog.ui'
**
** Created: Sun Sep 4 07:30:55 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEDIALOG_H
#define UI_PROFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_profileDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_avatar;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_fullName;
    QLabel *label_jid;
    QLabel *label_status;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *profileDialog)
    {
        if (profileDialog->objectName().isEmpty())
            profileDialog->setObjectName(QString::fromUtf8("profileDialog"));
        profileDialog->resize(309, 209);
        profileDialog->setSizeGripEnabled(true);
        verticalLayout_3 = new QVBoxLayout(profileDialog);
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea = new QScrollArea(profileDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 297, 168));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
#ifndef Q_OS_MAC
        verticalLayout_4->setSpacing(6);
#endif
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label_avatar = new QLabel(scrollAreaWidgetContents);
        label_avatar->setObjectName(QString::fromUtf8("label_avatar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_avatar->sizePolicy().hasHeightForWidth());
        label_avatar->setSizePolicy(sizePolicy);
        label_avatar->setMinimumSize(QSize(96, 96));
        label_avatar->setMaximumSize(QSize(96, 96));
        label_avatar->setPixmap(QPixmap(QString::fromUtf8(":/icons/resource/avatar.png")));
        label_avatar->setScaledContents(true);
        label_avatar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(label_avatar);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_fullName = new QLabel(scrollAreaWidgetContents);
        label_fullName->setObjectName(QString::fromUtf8("label_fullName"));

        verticalLayout->addWidget(label_fullName);

        label_jid = new QLabel(scrollAreaWidgetContents);
        label_jid->setObjectName(QString::fromUtf8("label_jid"));

        verticalLayout->addWidget(label_jid);

        label_status = new QLabel(scrollAreaWidgetContents);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setWordWrap(true);
        label_status->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(label_status);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(profileDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(profileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), profileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), profileDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(profileDialog);
    } // setupUi

    void retranslateUi(QDialog *profileDialog)
    {
        profileDialog->setWindowTitle(QApplication::translate("profileDialog", "Profile", 0, QApplication::UnicodeUTF8));
        label_avatar->setText(QString());
        label_fullName->setText(QApplication::translate("profileDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_jid->setText(QApplication::translate("profileDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_status->setText(QApplication::translate("profileDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class profileDialog: public Ui_profileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEDIALOG_H
