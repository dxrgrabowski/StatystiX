
#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QFileDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>


class InputForm : public QWidget
{
    Q_OBJECT
public:
    explicit InputForm(QWidget *parent = nullptr);

    QString selectedFile() const;
    void selectFile();

signals:
    void fileSelected(const QString &fileName);

private:
    QLineEdit *m_fileLineEdit;
};

#endif // INPUTFORM_H
