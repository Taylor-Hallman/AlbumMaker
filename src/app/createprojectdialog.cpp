#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"
#include "editormain.h"
#include "../widgets/filedropwidget.h"
#include <QFileDialog>
#include <QImageReader>
#include <QMediaMetaData>

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
    ui->nextBtn->setEnabled(false);
    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);
    QObject::connect(ui->coverArt, &FileDropWidget::imageDropped, this, &CreateProjectDialog::on_imageDropped);
    QObject::connect(ui->tracks, &FileDropWidget::audioDropped, this, &CreateProjectDialog::on_audioDropped);
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
        for (int row = 0; row < ui->tracksTable->rowCount(); row++)
            tracks.emplace_back(ui->tracksTable->item(row, 0)->text(), ui->tracksTable->item(row, 1)->text());
        EditorMain* window = new EditorMain();
        window->show();
        QObject::connect(this, &CreateProjectDialog::createdProject, window, &EditorMain::on_projectCreated);
        emit createdProject(projectName, albumName, artistName, coverArt, tracks);
        this->close();
    }
    else {
        ui->listWidget->setCurrentRow(++currRow);
        ui->stackedWidget->setCurrentIndex(currRow);
        ui->nextBtn->setText("Skip");
    }
}


void CreateProjectDialog::on_nameField_textEdited(const QString& text)
{
    ui->nextBtn->setEnabled(!ui->nameField->text().isEmpty());
    ui->albumNameField->setText(text);
}


void CreateProjectDialog::on_nameField_textChanged(const QString& text)
{
    projectName = text;
}


void CreateProjectDialog::on_albumNameField_textChanged(const QString& text)
{
    albumName = text;
}


void CreateProjectDialog::on_artistField_textChanged(const QString& text)
{
    artistName = text;
}

void CreateProjectDialog::on_browseBtn_clicked()
{
    QStringList formats;
    for (const QByteArray& format : QImageReader::supportedImageFormats())
        formats << "*." + format;

    QString filter = "Images (" + formats.join(' ') + ")";
    QString file = QFileDialog::getOpenFileName(this, "Select Image", "", filter);
    handleImage(file);
}


void CreateProjectDialog::on_addBtn_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Select Audio", "", "Audio Files (*.mp3 *.wav *.ogg *.flac)");
    for (const QString& file : std::as_const(files))
        handleAudio(file);
}


void CreateProjectDialog::on_removeBtn_clicked()
{
    QSet<int> rowSet = getSelectedRows();
    QVector<int> rows(rowSet.begin(), rowSet.end());
    std::sort(rows.begin(), rows.end(), std::greater<int>());
    for (int row : rows)
        ui->tracksTable->removeRow(row);

    if (ui->tracksTable->rowCount() == 0)
        ui->nextBtn->setText("Skip");
}

void CreateProjectDialog::on_imageDropped(const QString& path)
{
    handleImage(path);
}

void CreateProjectDialog::on_audioDropped(const QString& path) {
    handleAudio(path);
}


void CreateProjectDialog::on_downBtn_clicked()
{
    QSet<int> rows = getSelectedRows();
    Q_ASSERT(rows.count() == 1 && !rows.contains(ui->tracksTable->rowCount() - 1));
    int sourceRow = *rows.begin();
    int targetRow = sourceRow + 2;

    ui->tracksTable->insertRow(targetRow);
    for (int col = 0; col < ui->tracksTable->columnCount(); col++)
        ui->tracksTable->setItem(targetRow, col, ui->tracksTable->takeItem(sourceRow, col));
    ui->tracksTable->removeRow(sourceRow);
    ui->tracksTable->selectRow(targetRow - 1);
}


void CreateProjectDialog::on_upBtn_clicked()
{
    QSet<int> rows = getSelectedRows();
    Q_ASSERT(rows.count() == 1 && !rows.contains(0));
    int sourceRow = *rows.begin();
    int targetRow = sourceRow++ - 1;

    ui->tracksTable->insertRow(targetRow);
    for (int col = 0; col < ui->tracksTable->columnCount(); col++)
        ui->tracksTable->setItem(targetRow, col, ui->tracksTable->takeItem(sourceRow, col));
    ui->tracksTable->removeRow(sourceRow);
    ui->tracksTable->selectRow(targetRow);
}

void CreateProjectDialog::handleImage(const QString& path)
{
    if (ui->stackedWidget->currentIndex() != 1)
        return;
    if (!path.isEmpty()) {
        ui->fileTxt->setText(path);
        ui->nextBtn->setText("Next");
        QPixmap pixmap(path);
        if (pixmap.isNull())
            ui->imageLabel->setText("Failed to load image");
        else {
            ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size() * 0.8, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            coverArt = path;
        }
    }
}

void CreateProjectDialog::handleAudio(const QString& path) {
    if (ui->stackedWidget->currentIndex() != 2)
        return;
    if (!path.isEmpty()) {
        QFileInfo info(path);
        QString baseFileName = info.completeBaseName();
        int newRowIdx = ui->tracksTable->rowCount();
        ui->tracksTable->insertRow(newRowIdx);

        QMediaPlayer* tempPlayer = new QMediaPlayer(this);
        tempPlayer->setSource(QUrl::fromLocalFile(path));
        connect(tempPlayer, &QMediaPlayer::metaDataChanged, [this, tempPlayer, path, newRowIdx, baseFileName]() {
            QMediaMetaData meta = tempPlayer->metaData();

            QString title;

            QVariant trackTitle = meta.value(QMediaMetaData::Title);

            title = trackTitle.isNull() ? baseFileName : trackTitle.toString();
            ui->tracksTable->setItem(newRowIdx, 0, new QTableWidgetItem(title));
            tempPlayer->deleteLater();
        });
        QTableWidgetItem* pathItem = new QTableWidgetItem(path);
        pathItem->setFlags(pathItem->flags() & ~Qt::ItemIsEditable);
        ui->tracksTable->setItem(newRowIdx, 1, pathItem);
        ui->nextBtn->setText("Finish");
    }
}

QSet<int> CreateProjectDialog::getSelectedRows()
{
    const auto& selectedItems = ui->tracksTable->selectedItems();
    QSet<int> rows;
    for (auto item : selectedItems)
        rows.insert(item->row());
    return rows;
}

void CreateProjectDialog::on_tracksTable_itemSelectionChanged()
{
    QSet<int> rows = getSelectedRows();
    ui->upBtn->setEnabled(rows.count() == 1 && !rows.contains(0));
    ui->downBtn->setEnabled(rows.count() == 1 && !rows.contains(ui->tracksTable->rowCount() - 1));
    ui->removeBtn->setEnabled(rows.count() > 0);
}

