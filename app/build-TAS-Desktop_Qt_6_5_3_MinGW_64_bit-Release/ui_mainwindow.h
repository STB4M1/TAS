/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonLogStart;
    QPushButton *pushButtonLogStop;
    QPushButton *pushButtonOutputData;
    QLCDNumber *lcdNumberLumiVal;
    QLineEdit *lineEditCaliblationTemperature;
    QLabel *labelCaliblationTemperature;
    QLabel *label;
    QChartView *widgetLvGraph;
    QLineEdit *lineEditAveTemperature;
    QLabel *label_2;
    QComboBox *comboBoxPortName;
    QLabel *labelSerialPort;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(637, 369);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButtonLogStart = new QPushButton(centralwidget);
        pushButtonLogStart->setObjectName("pushButtonLogStart");
        pushButtonLogStart->setGeometry(QRect(30, 280, 141, 41));
        QFont font;
        font.setPointSize(20);
        pushButtonLogStart->setFont(font);
        pushButtonLogStop = new QPushButton(centralwidget);
        pushButtonLogStop->setObjectName("pushButtonLogStop");
        pushButtonLogStop->setGeometry(QRect(240, 280, 151, 41));
        pushButtonLogStop->setFont(font);
        pushButtonOutputData = new QPushButton(centralwidget);
        pushButtonOutputData->setObjectName("pushButtonOutputData");
        pushButtonOutputData->setGeometry(QRect(450, 280, 141, 41));
        pushButtonOutputData->setFont(font);
        lcdNumberLumiVal = new QLCDNumber(centralwidget);
        lcdNumberLumiVal->setObjectName("lcdNumberLumiVal");
        lcdNumberLumiVal->setGeometry(QRect(380, 10, 181, 101));
        lineEditCaliblationTemperature = new QLineEdit(centralwidget);
        lineEditCaliblationTemperature->setObjectName("lineEditCaliblationTemperature");
        lineEditCaliblationTemperature->setGeometry(QRect(470, 190, 113, 31));
        QFont font1;
        font1.setPointSize(12);
        lineEditCaliblationTemperature->setFont(font1);
        labelCaliblationTemperature = new QLabel(centralwidget);
        labelCaliblationTemperature->setObjectName("labelCaliblationTemperature");
        labelCaliblationTemperature->setGeometry(QRect(390, 190, 81, 41));
        labelCaliblationTemperature->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(580, 70, 41, 41));
        QFont font2;
        font2.setPointSize(30);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);
        widgetLvGraph = new QChartView(centralwidget);
        widgetLvGraph->setObjectName("widgetLvGraph");
        widgetLvGraph->setGeometry(QRect(30, 10, 341, 221));
        lineEditAveTemperature = new QLineEdit(centralwidget);
        lineEditAveTemperature->setObjectName("lineEditAveTemperature");
        lineEditAveTemperature->setGeometry(QRect(450, 130, 131, 51));
        lineEditAveTemperature->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(390, 150, 61, 31));
        QFont font3;
        font3.setPointSize(18);
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignCenter);
        comboBoxPortName = new QComboBox(centralwidget);
        comboBoxPortName->setObjectName("comboBoxPortName");
        comboBoxPortName->setGeometry(QRect(170, 240, 181, 31));
        labelSerialPort = new QLabel(centralwidget);
        labelSerialPort->setObjectName("labelSerialPort");
        labelSerialPort->setGeometry(QRect(60, 250, 101, 16));
        labelSerialPort->setFont(font1);
        labelSerialPort->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 637, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonLogStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pushButtonLogStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        pushButtonOutputData->setText(QCoreApplication::translate("MainWindow", "Log", nullptr));
        labelCaliblationTemperature->setText(QCoreApplication::translate("MainWindow", "<html>\n"
"<head></head>\n"
"<body>\n"
"    <p style=\"text-align: center;\">Caliblation<br>Temperature</p>\n"
"</body>\n"
"</html>\n"
"", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ave.", nullptr));
        labelSerialPort->setText(QCoreApplication::translate("MainWindow", "Serial Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
