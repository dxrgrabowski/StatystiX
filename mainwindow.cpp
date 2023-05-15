#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    //ui->lineEdit_pathName->setText(inputForm.selectedFile());

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


void MainWindow::on_testButton_clicked()
{
//    std::vector<QPointF> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};

//    Chart* chart = new Chart(points); // Tworzymy obiekt wykresu
//    chart->setAttribute(Qt::WA_DeleteOnClose);

//    m_chart->show();

    JsonTestDataGenerator jsonGenerator(0, 999, 9);
    jsonGenerator.generateTestData("testData.json");

    CsvTestDataGenerator csvGenerator(0, 999, 9);
    csvGenerator.generateTestData("testData.csv");


}

void MainWindow::loadFile(const QString &fileName) {
    QMessageBox::information(this, tr("Selected File"), tr("Selected file: %1").arg(fileName));
}


