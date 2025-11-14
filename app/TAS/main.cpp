#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon icon(":/icons/icon/TAS.ico");
    if (icon.isNull()) {
        qDebug() << "Icon could not be loaded.";
    } else {
        qDebug() << "Icon is loaded successfully.";
    }
    QApplication::setWindowIcon(icon);

    MainWindow w;
    w.show();
    return a.exec();
}
