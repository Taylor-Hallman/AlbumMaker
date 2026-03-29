#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"
#include "../widgets/imagedropwidget.h"
#include <QFileDialog>

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
    ui->nextBtn->setEnabled(false);
    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);
    QObject::connect(ui->coverArt, &ImageDropWidget::imageDropped, this, &CreateProjectDialog::on_imageDropped);
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
    int currRow = ui->listWidget->currentRow();
    if (currRow == ui->listWidget->count() - 1) {
        emit createdProject();
        this->close();
    }
    else {
        ui->listWidget->setCurrentRow(++currRow);
        ui->stackedWidget->setCurrentIndex(currRow);
        ui->nextBtn->setText("Skip");
    }
}


void CreateProjectDialog::on_nameField_textEdited(const QString&)
{
    ui->nextBtn->setEnabled(!ui->nameField->text().isEmpty());
}


void CreateProjectDialog::on_browseBtn_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif *.webp)");
    handleImage(file);
}

void CreateProjectDialog::on_imageDropped(const QString& path)
{
    handleImage(path);
}

void CreateProjectDialog::handleImage(const QString &path)
{
    if (!path.isEmpty()) {
        ui->fileTxt->setText(path);
        ui->nextBtn->setText("Next");
        QPixmap pixmap(path);
        if (pixmap.isNull())
            ui->imageLabel->setText("Failed to load image");
        else
            ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

