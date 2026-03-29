#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
    ui->nextBtn->setEnabled(false);
    ui->listWidget->setCurrentRow(0);
}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}

void CreateProjectDialog::on_cancelBtn_clicked()
{
    this->close();
}

void CreateProjectDialog::on_nextBtn_clicked()
{
    // todo
}


void CreateProjectDialog::on_nameField_textEdited(const QString&)
{
    ui->nextBtn->setEnabled(!ui->nameField->text().isEmpty());
}

