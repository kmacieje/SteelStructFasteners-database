#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QIcon>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Catalog @ Fasteners for Steel Structures");
    w.show();
    return a.exec();
}



