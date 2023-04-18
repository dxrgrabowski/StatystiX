#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDesktopServices>
#include "Dataset.h"
//#include "testdatagenerator.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFileButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"C:/","JSON file (*.json)");
    //QMessageBox::information(this,tr("File Name"), filename);
    ui->lineEdit_pathName->setText(filename);

    QPair<bool, QJsonObject> parseResult = parseFile(filename);

    if (!parseResult.first) {
        return;}

    QJsonObject obj = parseResult.second;

    Dataset x(obj.value("x").toArray());
    Dataset y(obj.value("y").toArray());

    QString XoutputText = QString("Min: %1\nMax: %2\nMean: %3\nMedian: %4\nStandard deviation: %5\nVariance: %6")
            .arg(x.minValue())
            .arg(x.maxValue())
            .arg(x.meanValue())
            .arg(x.medianValue())
            .arg(x.standardDeviationValue())
            .arg(x.varianceValue());

    QString YoutputText = QString("Min: %1\nMax: %2\nMean: %3\nMedian: %4\nStandard deviation: %5\nVariance: %6")
            .arg(y.minValue())
            .arg(y.maxValue())
            .arg(y.meanValue())
            .arg(y.medianValue())
            .arg(y.standardDeviationValue())
            .arg(y.varianceValue());


    ui->XoutputPlainTextEdit->setPlainText(XoutputText);
    ui->YoutputPlainTextEdit->setPlainText(YoutputText);
}



QPair<bool, QJsonObject> MainWindow::parseFile(QString& filename)
{
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("Error"), tr("Failed to open file"));
        return { false, QJsonObject() };
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (doc.isNull()){
        QMessageBox::warning(this, tr("Error"), tr("Failed to parse JSON"));
        return { false, QJsonObject() };
    }

    return { true, doc.object() };
}



void MainWindow::on_githubButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/dxrgrabowski/StatystiX", QUrl::TolerantMode));
}


void MainWindow::on_testButton_clicked()
{
    std::vector<QPointF> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};


//        JsonTestDataGenerator jsonGenerator(0, 100, 10);
//        jsonGenerator.generateTestData("testData.json");

//        CsvTestDataGenerator csvGenerator(0, 100, 10);
//        csvGenerator.generateTestData("testData.csv");


}
