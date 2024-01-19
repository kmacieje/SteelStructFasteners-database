#include "fastenerscollector.h"

using database = QVector<SFasteners>;

SFastenersCollector::SFastenersCollector(void) {}

///////////////////////////////////////////////////////////
// This function retrieves the reference to the FastenersVector.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		None.
//		
// OUTPUT:
//		Returns a constant reference to the FastenersVector.
//		
const database& SFastenersCollector::getFastenersVector(void) const
{
    return db;
}

///////////////////////////////////////////////////////////
// This function fills the database with a new record.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		itemNoLineEdit - QLineEdit for the item number.
//		elementLineEdit - QLineEdit for the element.
//		symbolLineEdit - QLineEdit for the symbol.
//		weightLineEdit - QLineEdit for the weight.
//		materialLineEdit - QLineEdit for the material.
//		surfaceLineEdit - QLineEdit for the surface.
//		propClassLineEdit - QLineEdit for the property class.
//		dinLineEdit - QLineEdit for the DIN number.
//		
// OUTPUT:
//		None.
//		
// REMARKS:
//		Ensure that all input parameters are valid QLineEdit objects.
//		The function uses the provided input to update the database
//		with fastener information. 
//
void SFastenersCollector::FillDataBase(QLineEdit* itemNoLineEdit, QLineEdit* elementLineEdit,
                                     QLineEdit* symbolLineEdit, QLineEdit* weightLineEdit,
                                     QLineEdit* materialLineEdit, QLineEdit* surfaceLineEdit,
                                     QLineEdit* propClassLineEdit, QLineEdit* dinLineEdit)
{
    int itemNo = itemNoLineEdit->text().toInt();
    QString element = elementLineEdit->text();
    QString symbol = symbolLineEdit->text();
    float weight = weightLineEdit->text().toFloat();
    QString material = materialLineEdit->text();
    QString surface = surfaceLineEdit->text();
    float propClass = propClassLineEdit->text().toFloat();
    int din = dinLineEdit->text().toInt();

    bool recordExists {false};
    for (const SFasteners &existingItem : db) {
        if (existingItem.getItemNo() == itemNo) {

            QMessageBox msgBox(QMessageBox::Critical, "Catalog @ Fasteners for Steel Structures", "A record with item number " + QString::number(itemNo) + " already exists! It is not possible to add an item to the database.", QMessageBox::Ok);
            msgBox.setStyleSheet("QLabel { color : black; }");  // change text color
            msgBox.exec();
            recordExists = true;
            break;
        }
    }

    if (itemNo == 0) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Item Number field cannot be 0! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }


    if (element.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Element field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }

    if (symbol.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Symbol field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }

    if (weight == 0.0) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Weight field cannot be 0! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }

    if (material.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Material field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }

    if (surface.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Surface field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }

    if (propClass == 0.0) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Property Class field cannot be 0! It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }

    if (din == 0) {
        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The DIN field cannot be 0! You should define the standard. It is not possible to add an item to the database.", QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color : black; }");  //to make the text visible
        msgBox.exec();
        return;
    }


    if (!recordExists && itemNo != 0 && !element.isEmpty() && !symbol.isEmpty() && weight != 0.0 && !material.isEmpty() && !surface.isEmpty() && propClass != 0.0 && !symbol.isEmpty()) {
    SFasteners record(itemNo, element, symbol, weight, material, surface, propClass, din);

    db.push_back(record);
    }
}

///////////////////////////////////////////////////////////
// This function deletes the record from the database.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		itemId - the item ID of the element to be deleted.
//		
// OUTPUT:
//		None.
//			
void SFastenersCollector::deleteRecord(int itemId)
{
    auto it = std::find_if(db.begin(), db.end(),
                           [itemId](const SFasteners& record) {
                               return record.getItemNo() == itemId;
                           });

    if (it != db.end()) {
        db.erase(it);
    }
}

///////////////////////////////////////////////////////////
// This function adds fastener records from a JSON file to the database.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		jsonFilePath - the file path of the JSON file containing fastener records.
//		
// OUTPUT:
//		None.
//		
// REMARKS:
//		Ensure that the provided JSON file path is valid and contains
//		correctly formatted fastener records. The function adds these
//		records to the database.
//	
void SFastenersCollector::addRecordsFromJsonFile(const QString& jsonFilePath)
{
    QFile jsonFile(jsonFilePath);

    if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = jsonFile.readAll();
        jsonFile.close();

        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);

        if (jsonError.error == QJsonParseError::NoError && jsonDoc.isArray())
        {
            QJsonArray jsonArray = jsonDoc.array();

            for (const QJsonValue& jsonValue : jsonArray)
            {
                if (jsonValue.isObject())
                {
                    QJsonObject jsonObj = jsonValue.toObject();

                    int itemNo = jsonObj["ItemNo"].toInt();
                    QString element = jsonObj["Element"].toString();
                    QString symbol = jsonObj["Symbol"].toString();
                    float weight = jsonObj["Weight"].toDouble();
                    QString material = jsonObj["Material"].toString();
                    QString surface = jsonObj["Surface"].toString();
                    float propClass = jsonObj["PropClass"].toDouble();
                    int din = jsonObj["DIN"].toInt();

                    bool recordExists {false};
                    for (const SFasteners &existingItem : db) {
                        if (existingItem.getItemNo() == itemNo) {

                            QMessageBox msgBox(QMessageBox::Critical, "Catalog @ Fasteners for Steel Structures", "A record with item number " + QString::number(itemNo) + " already exists! It is not possible to add an item to the database.", QMessageBox::Ok);
                            msgBox.setStyleSheet("QLabel { color : black; }");  
                            msgBox.exec();
                            recordExists = true;
                            break;
                        }
                    }

                    if (itemNo == 0) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Item Number field cannot be 0! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }");  
                        return;
                    }


                    if (element.isEmpty()) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Element field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }");  
                        msgBox.exec();
                        return;
                    }

                    if (symbol.isEmpty()) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Symbol field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }");  
                        msgBox.exec();
                        return;
                    }

                    if (weight == 0.0) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Weight field cannot be 0! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }");  
                        msgBox.exec();
                        return;
                    }

                    if (material.isEmpty()) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Material field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }"); 
                        msgBox.exec();
                        return;
                    }

                    if (surface.isEmpty()) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Surface field cannot be empty! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }"); 
                        return;
                    }

                    if (propClass == 0.0) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The Property Class field cannot be 0! It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }"); 
                        msgBox.exec();
                        return;
                    }

                    if (symbol.isEmpty()) {
                        QMessageBox msgBox(QMessageBox::Warning, "Catalog @ Fasteners for Steel Structures", "The DIN field cannot be empty! You should define the standard. It is not possible to add an item to the database.", QMessageBox::Ok);
                        msgBox.setStyleSheet("QLabel { color : black; }"); 
                        msgBox.exec();
                        return;
                    }

                    if (!recordExists && itemNo != 0 && !element.isEmpty() && !symbol.isEmpty() && weight != 0.0 && !material.isEmpty() && !surface.isEmpty() && propClass != 0.0 && !symbol.isEmpty()) {
                        SFasteners record(itemNo, element, symbol, weight, material, surface, propClass, din);

                        db.push_back(record);
                    }
                }
            }
        }
        else
        {
            qDebug() << "Error parsing JSON: " << jsonError.errorString();
        }
    }
    else
    {
        qDebug() << "Error opening JSON file";
    }
}

///////////////////////////////////////////////////////////
// This function saves fastener records from the database to a JSON file.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		filePath - the file path where the JSON file will be saved.
//		
// OUTPUT:
//		None.
//		
// REMARKS:
//		Ensure that the provided file path is valid and the necessary
//		permissions are granted. The function saves fastener records
//		from the database to the specified JSON file.
//	
void SFastenersCollector::saveToJsonFile(const QString &filePath) const
{
    QJsonArray jsonArray;

    for (const SFasteners &fastener : db) {
        QJsonObject jsonObj;
        jsonObj["ItemNo"] = fastener.getItemNo();
        jsonObj["Element"] = fastener.getElement();
        jsonObj["Symbol"] = fastener.getSymbol();
        jsonObj["Weight"] = fastener.getWeight();
        jsonObj["Material"] = fastener.getMaterial();
        jsonObj["Surface"] = fastener.getSurface();
        //jsonObj["PropClass"] = fastener.getPropClass();
        jsonObj["PropClass"] = round(fastener.getPropClass() * 10) / 10.0;  // set precision to one decimal place trick
        jsonObj["DIN"] = fastener.getDIN();

        jsonArray.append(jsonObj);
    }

    QJsonDocument jsonDoc(jsonArray);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(jsonDoc.toJson());
        file.close();
    } else {
        qDebug() << "The JSON file failed to open for writing.";
    }
}

///////////////////////////////////////////////////////////
// This function searches for fastener records in the database
// based on a specified column and search text.
///////////////////////////////////////////////////////////
//		
// INPUT:
//		columnName - the name of the column to search within.
//		searchText - the text to search for within the specified column.
//		
// OUTPUT:
//		Returns a new database containing fastener records that match
//		the search criteria.
//		
database SFastenersCollector::searchByColumn(const QString &columnName, const QString &searchText) const
{
    database searchResults;

    if (columnName == "ItemNo") {
        int searchValue = searchText.toInt();
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchValue](const SFasteners &fastener) {
            return fastener.getItemNo() == searchValue;
        });
    } else if (columnName == "Element") {
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchText](const SFasteners &fastener) {
            return fastener.getElement() == searchText;
        });
    } else if (columnName == "Symbol") {
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchText](const SFasteners &fastener) {
            return fastener.getSymbol() == searchText;
        });
    } else if (columnName == "Weight") {
        float searchValue = searchText.toDouble();
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchValue](const SFasteners &fastener) {
            return fastener.getWeight() == searchValue;
        });
    } else if (columnName == "Material") {
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchText](const SFasteners &fastener) {
            return fastener.getMaterial() == searchText;
        });
    } else if (columnName == "Surface") {
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchText](const SFasteners &fastener) {
            return fastener.getSurface() == searchText;
        });
    } else if (columnName == "Prop. Class") {
        float searchValue = searchText.toDouble();
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchValue](const SFasteners &fastener) {
            return fastener.getPropClass() == searchValue;
        });
    } else if (columnName == "DIN") {
        int searchValue = searchText.toInt();
        std::copy_if(db.begin(), db.end(), std::back_inserter(searchResults), [searchValue](const SFasteners &fastener) {
            return fastener.getDIN() == searchValue;
        });
    }

    return searchResults;
}
