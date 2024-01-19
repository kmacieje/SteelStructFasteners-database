#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QString>
#include "fastenerscollector.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_deleteButton_clicked();
    void on_refreshButton_clicked();
    void on_loadJsonButton_clicked();
    void on_saveButton_clicked();
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    void addRowToTable(const SFasteners &fastener);
    SFastenersCollector fDataBase;
    int deleteId;

};
#endif // MAINWINDOW_H
