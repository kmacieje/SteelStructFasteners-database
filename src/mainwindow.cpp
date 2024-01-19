#include "mainwindow.h"
#include "ui_mainwindow.h"

using database = QVector<SFasteners>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headers = {"ItemNo", "Element", "Symbol", "Weight", "Material", "Surface", "Prop. Class", "DIN"};
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemClicked(QTableWidgetItem*)));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));

    ui->columnComboBox->addItems(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


///////////////////////////////////////////////////////////
// This function adds a row to the table widget in the MainWindow
// with information from the provided SFasteners object.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		fastener - SFasteners object containing information for the new row.
//		
// OUTPUT:
//		None.
//		
void MainWindow::addRowToTable(const SFasteners &fastener)
{
    int rowPosition = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowPosition);

    ui->tableWidget->setItem(rowPosition, 0, new QTableWidgetItem(QString::number(fastener.getItemNo())));
    ui->tableWidget->setItem(rowPosition, 1, new QTableWidgetItem(fastener.getElement()));
    ui->tableWidget->setItem(rowPosition, 2, new QTableWidgetItem(fastener.getSymbol()));
    ui->tableWidget->setItem(rowPosition, 3, new QTableWidgetItem(QString::number(fastener.getWeight())));
    ui->tableWidget->setItem(rowPosition, 4, new QTableWidgetItem(fastener.getMaterial()));
    ui->tableWidget->setItem(rowPosition, 5, new QTableWidgetItem(fastener.getSurface()));
    ui->tableWidget->setItem(rowPosition, 6, new QTableWidgetItem(QString::number(fastener.getPropClass())));
    ui->tableWidget->setItem(rowPosition, 7, new QTableWidgetItem(QString::number(fastener.getDIN())));
}

///////////////////////////////////////////////////////////
// Slot function triggered when the "Add" button is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_addButton_clicked()
{
    fDataBase.FillDataBase(ui->itemNoLineEdit, ui->elementLineEdit,
                                   ui->symbolLineEdit, ui->weightLineEdit,
                                   ui->materialLineEdit, ui->surfaceLineEdit,
                                   ui->propClassLineEdit, ui->dinLineEdit);

    on_refreshButton_clicked();

    ui->itemNoLineEdit->clear();
    ui->elementLineEdit->clear();
    ui->symbolLineEdit->clear();
    ui->weightLineEdit->clear();
    ui->materialLineEdit->clear();
    ui->surfaceLineEdit->clear();
    ui->propClassLineEdit->clear();
    ui->dinLineEdit->clear();
}

///////////////////////////////////////////////////////////
// Slot function triggered when an item in the tableWidget is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if (item->row() >= 0) {
        int itemIdToDelete = ui->tableWidget->item(item->row(), 0)->text().toInt();

        deleteId = itemIdToDelete;
    }
}

///////////////////////////////////////////////////////////
// Slot function triggered when the "Delete element" button is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_deleteButton_clicked()
{
    if (deleteId != -1) {
        fDataBase.deleteRecord(deleteId);

        on_refreshButton_clicked();

        deleteId = -1;
    }
}

///////////////////////////////////////////////////////////
// Slot function triggered when the "Refresh list" button is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_refreshButton_clicked()
{
    const database& fastenersFromDatabase = fDataBase.getFastenersVector();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (const SFasteners& record : fastenersFromDatabase) {
        addRowToTable(record);
    }
}

///////////////////////////////////////////////////////////
// Slot function triggered when the "Import" button is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_loadJsonButton_clicked()
{
    QString jsonFilePath = QFileDialog::getOpenFileName(this, tr("Open JSON File"), "", tr("JSON Files (*.json)"));

    if (!jsonFilePath.isEmpty())
    {
        fDataBase.addRecordsFromJsonFile(jsonFilePath);

        on_refreshButton_clicked();
    }
}

///////////////////////////////////////////////////////////
// Slot function triggered when the "Export" button is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_saveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save the database to JSON file", "", "JSON files (*.json)");
    if (!filePath.isEmpty()) {
        fDataBase.saveToJsonFile(filePath);
        qDebug() << "Database saved to a JSON file: " << filePath;
    }
}

///////////////////////////////////////////////////////////
// Slot function triggered when the "Search" button is clicked
// in the MainWindow.
///////////////////////////////////////////////////////////
void MainWindow::on_searchButton_clicked()
{
    QString searchColumn = ui->columnComboBox->currentText();
    QString searchText = ui->searchLineEdit->text();

    if (searchColumn.isEmpty() || searchText.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "Enter both search values.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make it visible
        msgBox.exec();
        return;
    }

    database searchResults = fDataBase.searchByColumn(searchColumn, searchText);

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (const SFasteners& foundRecord : searchResults) {
        addRowToTable(foundRecord);
    }

    QMessageBox msgBox(QMessageBox::Information, "Catalog @ Fasteners for Steel Structures", "Found " + QString::number(searchResults.size()) + " results.", QMessageBox::Ok);
    msgBox.setStyleSheet("QLabel { color : black; }");
    msgBox.exec();

    ui->searchLineEdit->clear();
}
