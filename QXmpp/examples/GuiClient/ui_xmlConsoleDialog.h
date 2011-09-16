/********************************************************************************
** Form generated from reading UI file 'xmlConsoleDialog.ui'
**
** Created: Sun Sep 4 07:30:55 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XMLCONSOLEDIALOG_H
#define UI_XMLCONSOLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_xmlConsoleDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QLabel *label_legend;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_enable;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_clear;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *xmlConsoleDialog)
    {
        if (xmlConsoleDialog->objectName().isEmpty())
            xmlConsoleDialog->setObjectName(QString::fromUtf8("xmlConsoleDialog"));
        xmlConsoleDialog->resize(569, 349);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/resource/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        xmlConsoleDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(xmlConsoleDialog);
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(xmlConsoleDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        label_legend = new QLabel(xmlConsoleDialog);
        label_legend->setObjectName(QString::fromUtf8("label_legend"));

        verticalLayout->addWidget(label_legend);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox_enable = new QCheckBox(xmlConsoleDialog);
        checkBox_enable->setObjectName(QString::fromUtf8("checkBox_enable"));
        checkBox_enable->setChecked(true);

        horizontalLayout->addWidget(checkBox_enable);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_clear = new QPushButton(xmlConsoleDialog);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        horizontalLayout->addWidget(pushButton_clear);

        buttonBox = new QDialogButtonBox(xmlConsoleDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(xmlConsoleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), xmlConsoleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), xmlConsoleDialog, SLOT(reject()));
        QObject::connect(pushButton_clear, SIGNAL(clicked()), textBrowser, SLOT(clear()));

        QMetaObject::connectSlotsByName(xmlConsoleDialog);
    } // setupUi

    void retranslateUi(QDialog *xmlConsoleDialog)
    {
        xmlConsoleDialog->setWindowTitle(QApplication::translate("xmlConsoleDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_legend->setText(QApplication::translate("xmlConsoleDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        checkBox_enable->setText(QApplication::translate("xmlConsoleDialog", "Enable", 0, QApplication::UnicodeUTF8));
        pushButton_clear->setText(QApplication::translate("xmlConsoleDialog", "Clear", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class xmlConsoleDialog: public Ui_xmlConsoleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XMLCONSOLEDIALOG_H
