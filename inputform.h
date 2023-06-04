
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
    QString selectedFolder() const;

    void selectFile();
    void selectFolder();

signals:
    void fileSelected(const QString &fileName);
    void folderSelected(const QString &fileName);
private:
    QLineEdit *m_fileLineEdit;   
    QLineEdit *m_folderLineEdit;
};

#endif // INPUTFORM_H
