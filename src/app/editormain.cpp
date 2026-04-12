#include "editormain.h"
#include "ui_editormain.h"
#include <QIcon>
#include <QMediaMetaData>

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
    ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Artist
    ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Duration

    for (int i = 0; i < trackPaths.size(); i++) {
        auto& [name, path] = trackPaths.at(i);
        ui->tracksTableWidget->insertRow(i);
        QTableWidgetItem* titleItem = new QTableWidgetItem(name);
        titleItem->setData(Qt::UserRole, path);
        ui->tracksTableWidget->setItem(i, 0, titleItem);
        ui->tracksTableWidget->setItem(i, 1, new QTableWidgetItem());
        ui->tracksTableWidget->setItem(i, 2, new QTableWidgetItem());

        // get the track duration
        QMediaPlayer* tempPlayer = new QMediaPlayer(this);
        QAudioOutput* tempAudio = new QAudioOutput(tempPlayer);
        tempPlayer->setAudioOutput(tempAudio);
        tempPlayer->setSource(QUrl::fromLocalFile(path));

        auto hasMeta = std::make_shared<bool>(false);
        auto hasDuration = std::make_shared<bool>(false);

        connect(tempPlayer, &QMediaPlayer::metaDataChanged, this, [this, tempPlayer, i, artistName, hasMeta, hasDuration]() {
            QMediaMetaData meta = tempPlayer->metaData();
            QVariant artist = meta.value(QMediaMetaData::ContributingArtist);
            QString text = artist.isNull() ? artistName : artist.toString();

            ui->tracksTableWidget->item(i, 1)->setText(text);
            *hasMeta = true;
            if (hasDuration)
                tempPlayer->deleteLater();
        });

        connect(tempPlayer, &QMediaPlayer::durationChanged, this, [this, tempPlayer, i, &hasMeta, &hasDuration](qint64 duration) {
            if (duration <= 0)
                return;
            int seconds = duration / 1000, minutes = seconds / 60;
            seconds %= 60;

            QString text = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));

            ui->tracksTableWidget->item(i, 2)->setText(text);
            ui->tracksTableWidget->item(i, 2)->setData(Qt::UserRole, duration);
            *hasDuration = true;
            if (hasMeta)
                tempPlayer->deleteLater();
        });

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

