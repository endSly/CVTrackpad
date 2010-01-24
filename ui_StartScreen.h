/********************************************************************************
** Form generated from reading ui file 'StartScreen.ui'
**
** Created: Sun Jun 14 15:12:23 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartScreen
{
public:
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *startImageLabel;
    QLabel *label;

    void setupUi(QDialog *StartScreen)
    {
        if (StartScreen->objectName().isEmpty())
            StartScreen->setObjectName(QString::fromUtf8("StartScreen"));
        StartScreen->resize(699, 320);
        layoutWidget = new QWidget(StartScreen);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 708, 302));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        startImageLabel = new QLabel(layoutWidget);
        startImageLabel->setObjectName(QString::fromUtf8("startImageLabel"));
        startImageLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/CVTrackpad loadscreen.bmp")));

        formLayout->setWidget(0, QFormLayout::LabelRole, startImageLabel);

        label = new QLabel(StartScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(430, 300, 221, 20));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(StartScreen);

        QMetaObject::connectSlotsByName(StartScreen);
    } // setupUi

    void retranslateUi(QDialog *StartScreen)
    {
        StartScreen->setWindowTitle(QApplication::translate("StartScreen", "Dialog", 0, QApplication::UnicodeUTF8));
        startImageLabel->setText(QString());
        label->setText(QApplication::translate("StartScreen", "CVTrackpad", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StartScreen);
    } // retranslateUi

};

namespace Ui {
    class StartScreen: public Ui_StartScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
