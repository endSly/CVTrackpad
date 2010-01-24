/********************************************************************************
** Form generated from reading ui file 'CameraDeviceDialog.ui'
**
** Created: Sun Jun 14 15:12:23 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CAMERADEVICEDIALOG_H
#define UI_CAMERADEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CameraDeviceDialog
{
public:
    QLabel *cameraDeviceLabel;
    QCheckBox *defaultDeviceCheckBox;
    QPushButton *confirmCameraDevice;
    QSpinBox *spinBox;

    void setupUi(QDialog *CameraDeviceDialog)
    {
        if (CameraDeviceDialog->objectName().isEmpty())
            CameraDeviceDialog->setObjectName(QString::fromUtf8("CameraDeviceDialog"));
        CameraDeviceDialog->resize(321, 113);
        cameraDeviceLabel = new QLabel(CameraDeviceDialog);
        cameraDeviceLabel->setObjectName(QString::fromUtf8("cameraDeviceLabel"));
        cameraDeviceLabel->setGeometry(QRect(20, 10, 181, 31));
        QFont font;
        font.setPointSize(14);
        cameraDeviceLabel->setFont(font);
        defaultDeviceCheckBox = new QCheckBox(CameraDeviceDialog);
        defaultDeviceCheckBox->setObjectName(QString::fromUtf8("defaultDeviceCheckBox"));
        defaultDeviceCheckBox->setGeometry(QRect(30, 80, 101, 20));
        confirmCameraDevice = new QPushButton(CameraDeviceDialog);
        confirmCameraDevice->setObjectName(QString::fromUtf8("confirmCameraDevice"));
        confirmCameraDevice->setGeometry(QRect(200, 70, 111, 31));
        QFont font1;
        font1.setPointSize(10);
        confirmCameraDevice->setFont(font1);
        spinBox = new QSpinBox(CameraDeviceDialog);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(270, 20, 41, 22));

        retranslateUi(CameraDeviceDialog);

        QMetaObject::connectSlotsByName(CameraDeviceDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraDeviceDialog)
    {
        CameraDeviceDialog->setWindowTitle(QApplication::translate("CameraDeviceDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cameraDeviceLabel->setText(QApplication::translate("CameraDeviceDialog", "Seleccione dispositivo", 0, QApplication::UnicodeUTF8));
        defaultDeviceCheckBox->setText(QApplication::translate("CameraDeviceDialog", "Por defecto", 0, QApplication::UnicodeUTF8));
        confirmCameraDevice->setText(QApplication::translate("CameraDeviceDialog", "OK", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CameraDeviceDialog);
    } // retranslateUi

};

namespace Ui {
    class CameraDeviceDialog: public Ui_CameraDeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERADEVICEDIALOG_H
