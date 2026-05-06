#include <QString>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDialogButtonBox>

#include "../serialization/projectio.h"

#include "savedialog.h"
#include "ui_savedialog.h"

SaveDialog::SaveDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::on_ProjectDataReceived(Project& p, QString path)
{
    project = p;
    QString fileName = p.albumName;
    std::replace(fileName.begin(), fileName.end(), ' ', '_');
    ui->nameField->setText(fileName);

    if (!path.isEmpty())
        ui->pathField->setText(path);
}

void SaveDialog::openFileDialog()
{
    QString path = ui->pathField->text().isEmpty() ?
                       QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) :
                       ui->pathField->text();

    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Select Directory"),
        path,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (!dir.isEmpty()) {
        ui->pathField->setText(dir);
    }
}
void SaveDialog::on_chooseDirBtn_clicked()
{
    openFileDialog();
}


void SaveDialog::on_buttonBox_accepted()
{
    Q_ASSERT(!ui->nameField->text().isEmpty() && !ui->pathField->text().isEmpty());

    QString filePath = ui->pathField->text() + "/" + ui->nameField->text();
    ProjectIO::saveToFile(project, filePath);
    this->close();
}

void SaveDialog::on_buttonBox_rejected()
{
    this->close();
}


void SaveDialog::on_nameField_textChanged(const QString&)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(!ui->nameField->text().isEmpty() && !ui->pathField->text().isEmpty());
}


void SaveDialog::on_pathField_textChanged(const QString&)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(!ui->nameField->text().isEmpty() && !ui->pathField->text().isEmpty());
}