#ifndef SFASTENERSCOLLECTOR_H
#define SFASTENERSCOLLECTOR_H

#include "fasteners.h"
#include <QVector>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QString>
#include <algorithm>
#include <math.h>


using database = QVector<SFasteners>;

class SFastenersCollector
{
private:
    database db;
public:
     SFastenersCollector(void);

//public:
//    SFastenersCollector(void) = default;
//   virtual ~SFastenersCollector() = default;

    const database& getFastenersVector(void) const;

    void FillDataBase(QLineEdit* itemNoLineEdit, QLineEdit* elementLineEdit,
                       QLineEdit* symbolLineEdit, QLineEdit* weightLineEdit,
                       QLineEdit* materialLineEdit, QLineEdit* surfaceLineEdit,
                       QLineEdit* propClassLineEdit, QLineEdit* dinLineEdit);  //passing by reference may be less efficient

    void deleteRecord(int itemId);
    void addRecordsFromJsonFile(const QString& jsonFilePath);
    void saveToJsonFile(const QString &filePath) const;
    QVector<SFasteners> searchByColumn(const QString &columnName, const QString &searchText) const;

};

#endif  // SFASTENERSCOLLECTOR_H
