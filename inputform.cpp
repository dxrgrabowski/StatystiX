#include "inputform.h"

InputForm::InputForm(QWidget *parent)
    : QWidget(parent)
    , m_fileLineEdit(new QLineEdit(this))
{
    QFormLayout *formLayout = new QFormLayout(this);
    QPushButton *fileButton = new QPushButton(tr("Select File"), this);

    formLayout->addRow(tr("File:"), m_fileLineEdit);
    formLayout->addWidget(fileButton);

    connect(fileButton, &QPushButton::clicked, this, &InputForm::selectFile);
}

QString InputForm::selectedFile() const {
    return m_fileLineEdit->text();
}

void InputForm::selectFile() {
    const QString fileName = QFileDialog::getOpenFileName(this,
                                                          tr("Open File"), "", tr("Files (*.json *.csv)"));

    if(!fileName.isEmpty()) {
        m_fileLineEdit->setText(fileName);
        emit fileSelected(fileName);
    }
}
