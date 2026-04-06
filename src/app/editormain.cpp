#include "editormain.h"
#include "ui_editormain.h"
#include <QIcon>

EditorMain::EditorMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorMain)
{
    ui->setupUi(this);
    this->showMaximized();

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    connect(ui->tracksTableWidget, &QTableWidget::cellClicked, this, &EditorMain::on_trackActivated);
}

EditorMain::~EditorMain()
{
    delete ui;
}

void EditorMain::on_projectCreated(QString projectName, QString albumName, QString artistName, QString coverArtPath, QVector<std::pair<QString, QString>> trackPaths)
{
    setWindowTitle(projectName);
    if (albumName.size() > 0)
        ui->albumName->setText(albumName);
    if (artistName.size() > 0)
        ui->artistName->setText(artistName);
    QPixmap pixmap(coverArtPath);
    if (pixmap.isNull())
        ui->coverArt->setText("Failed to load image");
    else
        ui->coverArt->setPixmap(pixmap.scaled(ui->coverArt->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->tracksTableWidget->setColumnCount(3);ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);      // Title
    ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents); // Artist
    ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Duration

    for (int i = 0; i < trackPaths.size(); i++) {
        auto& [name, path] = trackPaths.at(i);
        ui->tracksTableWidget->insertRow(i);
        QTableWidgetItem* titleItem = new QTableWidgetItem(name);
        titleItem->setData(Qt::UserRole, path);
        ui->tracksTableWidget->setItem(i, 0, titleItem);
        ui->tracksTableWidget->setItem(i, 1, new QTableWidgetItem(artistName));
        ui->tracksTableWidget->setItem(i, 2, new QTableWidgetItem("3:45")); // placeholder for now
    }
}

void EditorMain::on_trackActivated(int row, int column)
{
    Q_UNUSED(column);
    playTrack(row);
}

void EditorMain::playTrack(int trackIdx)
{
     QTableWidgetItem* item = ui->tracksTableWidget->item(trackIdx, 0);
    if (!item)
        return;

    QString filePath = item->data(Qt::UserRole).toString();
    if (filePath.isEmpty())
        return;

    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    ui->playBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
    isPlaying = true;
}

void EditorMain::on_playAlbumBtn_clicked()
{
    playTrack(0);
}


void EditorMain::on_playBtn_clicked()
{
    if (isPlaying) {
        isPlaying = false;
        player->pause();
        ui->playBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
    }
    else {
        player->play();
        ui->playBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        isPlaying = true;
    }
}

QSet<int> EditorMain::getSelectedRows()
{
    const auto& selectedItems = ui->tracksTableWidget->selectedItems();
    QSet<int> rows;
    for (auto item : selectedItems)
        rows.insert(item->row());
    return rows;
}

