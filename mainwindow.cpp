#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chart.h"
#include "dataset.h"
#include "testdatagenerator.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , inputForm(new InputForm(this))
    , ui(new Ui::MainWindow)
{
    //setCentralWidget(inputForm);

    //connect(inputForm, &InputForm::fileSelected, this, &MainWindow::loadFile);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFileButton_clicked()
{
    inputForm.selectFile();
    ui->pathNameXY->setText(inputForm.selectedFile());

    auto parseResult = parser.parseFile(inputForm.selectedFile());

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

void MainWindow::on_githubButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/dxrgrabowski/StatystiX", QUrl::TolerantMode));
}

void MainWindow::loadFile(const QString &fileName) {
    QMessageBox::information(this, tr("Selected File"), tr("Selected file: %1").arg(fileName));
}



void MainWindow::on_XnadYBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_generatorBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_graphBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    switch(arg1){
    case 0:
        ui->manualText->setText("Click the “Open file” button, find your .json file.\n\nfile should be in JSON format, example: \n{ \n\"x\":[1714,1842,1786],\n\"y\"[2.4,3.08,2.17,3.19] \n}\n\n\"x\" or \"y\" container can be of any type int or double. \nThere must be two values in the file (\"x\" and \"y\") output is generated in fields \"The X\" and \"The Y\".\n\nAfter successfully selecting the correct file for X and Y, \nthe following values will be calculated:\n- min\n- max\n- mean\n- median\n- standard deviation\n- variance");
        break;
    case 2:
        ui->manualText->setText("Click the “Open file” button and choose loc.\n\nWhere the generated file should me stored.\n\nChoose desired file extension .json or .csv by selectiong one.\n\nClick generate to make a randomized file in desired localisation.");
        break;
    case 1:
        ui->manualText->setText("Choose the localisation of file containing data in desired format:\n{ \n\"x\":[1714,1842,1786],\n\"y\"[2.4,3.08,2.17,3.19] \n}\n\n for .json data, or exact type .csv document");
        break;
    }
}


void MainWindow::on_genOpenFileButton_clicked()
{

}


void MainWindow::on_dataSize_editingFinished()
{
    testDataGen.m_dataSize = ui->dataSize->value();
    printf("%d",testDataGen.m_dataSize);
}


void MainWindow::on_minValue_editingFinished()
{
    testDataGen.m_minValue = ui->minValue->value();
    printf("%d",testDataGen.m_minValue);
}


void MainWindow::on_maxValue_editingFinished()
{
    testDataGen.m_maxValue = ui->maxValue->value();
    printf("%d",testDataGen.m_maxValue);
}


void MainWindow::on_openFileButtonGenerator_clicked()
{
    inputForm.selectFolder();
    ui->pathNameGenerator->setText(inputForm.selectedFolder());
    testDataGen.filePath = inputForm.selectedFolder();
}


void MainWindow::on_radioJson_clicked()
{
    testDataGen.state = "json";
}


void MainWindow::on_radioCsv_clicked()
{
    testDataGen.state = "csv";
}


void MainWindow::on_pushButton_2_clicked()
{
    if(testDataGen.state == "NULL" || testDataGen.m_dataSize==NULL || (testDataGen.m_maxValue-testDataGen.m_minValue) <=0)
    {
        QMessageBox::warning(nullptr, "Error", "Wrong parameters");
        return;
    }
    else if(testDataGen.state == "json"){
        testDataGen.generateJsonTestData();
    }

    else if(testDataGen.state == "csv"){
        testDataGen.generateCsvTestData();
    }
}

void MainWindow::on_pushButton_clicked()
{
    std::vector<QPointF> points;

    auto parseResult = parser.parseFile(inputForm.selectedFile());
    if (!parseResult.first) {
        return;}

    QJsonObject obj = parseResult.second;

    if (obj.contains("x") && obj.contains("y")) {
        QJsonValue xVal = obj.value("x");
        QJsonValue yVal = obj.value("y");

        if (xVal.isArray() && yVal.isArray()) {
            QJsonArray xArray = xVal.toArray();
            QJsonArray yArray = yVal.toArray();

            if (xArray.size() == yArray.size()) {
                for (int i = 0; i < xArray.size(); ++i) {
                    if (xArray[i].isDouble() && yArray[i].isDouble()) {
                        double x = xArray[i].toDouble();
                        double y = yArray[i].toDouble();

                        points.push_back(QPointF(x, y));
                    }
                }
            } else {
                QMessageBox::warning(this, "Error", "Size mismatch between 'x' and 'y' arrays");
            }
        } else {
            QMessageBox::warning(this, "Error", "'x' and 'y' values are not arrays");
        }
    } else {
        QMessageBox::warning(this, "Error", "Required keys 'x' and 'y' not found");
    }

    Chart* chart = new Chart(points);
    chart->setAttribute(Qt::WA_DeleteOnClose);

    chart->resize(800, 800);
    chart->show();
}


void MainWindow::on_graphOpenFileButton_clicked()
{
    inputForm.selectFile();
    ui->pathNameGraph->setText(inputForm.selectedFile());
}

