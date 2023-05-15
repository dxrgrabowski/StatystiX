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
#include "chart.h"
#include "fileparser.h"
#include "inputform.h"

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
private slots:
    void on_openFileButton_clicked();
    void on_githubButton_clicked();
    void on_testButton_clicked();

    void loadFile(const QString &fileName);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
