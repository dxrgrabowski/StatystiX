#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDesktopServices>
#include "fileparser.h"
#include "inputform.h"
#include "testdatagenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    InputForm inputForm;
    FileParser parser;
    TestDataGenerator testDataGen;
private slots:
    void on_openFileButton_clicked();
    void on_githubButton_clicked();

    void loadFile(const QString &fileName);


    void on_XnadYBtn_clicked();

    void on_generatorBtn_clicked();

    void on_graphBtn_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_genOpenFileButton_clicked();

    void on_dataSize_editingFinished();

    void on_minValue_editingFinished();

    void on_maxValue_editingFinished();

    void on_openFileButtonGenerator_clicked();

    void on_radioJson_clicked();

    void on_radioCsv_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_graphOpenFileButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
