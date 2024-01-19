#include <QtTest/QtTest>
#include "../src/fastenerscollector.h"

class TestSteelStructFasteners : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        qDebug("Called before everything else.");
    }

    void testAddRecord()
    {
        SFastenersCollector database;

        QLineEdit itemNoLineEdit, elementLineEdit, symbolLineEdit, weightLineEdit,
            materialLineEdit, surfaceLineEdit, propClassLineEdit, dinLineEdit;

        itemNoLineEdit.setText("1");
        elementLineEdit.setText("Bolt");
        symbolLineEdit.setText("M16X50");
        weightLineEdit.setText("0.102");
        materialLineEdit.setText("Stainless Steel");
        surfaceLineEdit.setText("Black");
        propClassLineEdit.setText("8.8");
        dinLineEdit.setText("933");

        QVERIFY(database.getFastenersVector().isEmpty());
        database.FillDataBase(&itemNoLineEdit, &elementLineEdit, &symbolLineEdit,
                               &weightLineEdit, &materialLineEdit, &surfaceLineEdit,
                               &propClassLineEdit, &dinLineEdit);
        QCOMPARE(database.getFastenersVector().size(), 1);
    }

    void testDeleteRecord()
    {
        SFastenersCollector database;

        QLineEdit itemNoLineEdit, elementLineEdit, symbolLineEdit, weightLineEdit,
            materialLineEdit, surfaceLineEdit, propClassLineEdit, dinLineEdit;

        itemNoLineEdit.setText("1");
        elementLineEdit.setText("Bolt");
        symbolLineEdit.setText("M14X30");
        weightLineEdit.setText("0.054");
        materialLineEdit.setText("Stainless Steel");
        surfaceLineEdit.setText("Electrolytic zinc");
        propClassLineEdit.setText("8.8");
        dinLineEdit.setText("933");

        database.FillDataBase(&itemNoLineEdit, &elementLineEdit, &symbolLineEdit,
                              &weightLineEdit, &materialLineEdit, &surfaceLineEdit,
                              &propClassLineEdit, &dinLineEdit);

        itemNoLineEdit.setText("2");
        elementLineEdit.setText("Nut");
        symbolLineEdit.setText("M14");
        weightLineEdit.setText("0.0242");
        materialLineEdit.setText("Stainless Steel");
        surfaceLineEdit.setText("Electrolytic zinc");
        propClassLineEdit.setText("8");
        dinLineEdit.setText("934");

        database.FillDataBase(&itemNoLineEdit, &elementLineEdit, &symbolLineEdit,
                              &weightLineEdit, &materialLineEdit, &surfaceLineEdit,
                              &propClassLineEdit, &dinLineEdit);

        itemNoLineEdit.setText("3");
        elementLineEdit.setText("Washer");
        symbolLineEdit.setText("d15");
        weightLineEdit.setText("0.00861");
        materialLineEdit.setText("Stainless Steel");
        surfaceLineEdit.setText("Electrolytic zinc");
        propClassLineEdit.setText("200");
        dinLineEdit.setText("125");

        database.FillDataBase(&itemNoLineEdit, &elementLineEdit, &symbolLineEdit,
                              &weightLineEdit, &materialLineEdit, &surfaceLineEdit,
                              &propClassLineEdit, &dinLineEdit);

        QVERIFY(database.getFastenersVector().size() > 0);

        int IDToDelete = database.getFastenersVector().at(0).getItemNo();

        int initialRowCount = database.getFastenersVector().size();

        database.deleteRecord(IDToDelete);

        QVERIFY(database.getFastenersVector().size() == initialRowCount - 1);

        QVERIFY(std::none_of(database.getFastenersVector().begin(), database.getFastenersVector().end(),
                             [IDToDelete](const SFasteners& fastener) { return fastener.getItemNo() == IDToDelete; }));
    }

    void cleanupTestCase()
    {
        qDebug("Called after testAddRecord and testDeleteRecord.");
    }

};

QTEST_MAIN(TestSteelStructFasteners)
#include "Test.moc"
