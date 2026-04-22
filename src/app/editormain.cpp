#include "editormain.h"
#include "ui_editormain.h"
#include <QIcon>
#include <QMediaMetaData>
#include <QFileDialog>
#include <QTimer>

EditorMain::EditorMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorMain)
{
    ui->setupUi(this);
    this->showMaximized();

    ui->mediaPlayerUI->hide();

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);

    connect(ui->tracksTableWidget, &QTableWidget::cellDoubleClicked, this, &EditorMain::on_trackActivated);
    connect(ui->tracksTableWidget, &QTableWidget::customContextMenuRequested, this, &EditorMain::on_tableContextMenu);
    connect(ui->tracksTableWidget, &ReorderableTableWidget::rowReordered, this, &EditorMain::on_TracksReordered);

    connect(ui->trackProgressBar, &AdjustableProgressBar::valueEdited, this, &EditorMain::trackProgressBarValueEdited);
    connect(ui->trackProgressBar, &AdjustableProgressBar::mouseDragged, this, &EditorMain::trackProgressBarMouseDragged);

    connect(player, &QMediaPlayer::positionChanged, this, &EditorMain::trackPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &EditorMain::trackDurationChanged);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &EditorMain::trackStateChanged);
}

EditorMain::~EditorMain()
{
    delete ui;
}

void EditorMain::on_projectCreated(QString projectName, QString albumName, QString artistName, QString coverArtPath, QVector<QString> trackPaths)
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
    this->coverArtPath = coverArtPath;

    ui->tracksTableWidget->setColumnCount(3);ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);      // Title
    ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Artist
    ui->tracksTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Duration

    for (QString& path : trackPaths)
        handleAudio(path);
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

    unshuffledTrackQueue.clear();
    for (int row = trackIdx; row < ui->tracksTableWidget->rowCount(); row++) {
        QString path = ui->tracksTableWidget->item(row, 0)->data(Qt::UserRole).toString();
        unshuffledTrackQueue.emplaceFront(path, row);
    }

    trackQueue = unshuffledTrackQueue;
    playNext();
}

void EditorMain::playNext()
{
    if (trackQueue.isEmpty()) {
        ui->mediaPlayerUI->hide();
        ui->playAlbumBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        return;
    }

    auto [filePath, trackIdx] = trackQueue.pop();

    if (filePath.isEmpty())
        return;

    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    ui->playSongBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
    ui->playAlbumBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
    QPixmap pixmap(coverArtPath);
    if (!pixmap.isNull())
        ui->songImg->setPixmap(pixmap.scaled(ui->songImg->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->songTitle->setText(ui->tracksTableWidget->item(trackIdx, 0)->text());
    ui->songArtistName->setText(ui->tracksTableWidget->item(trackIdx, 1)->text());

    currTrackIdx = trackIdx;
}

void EditorMain::on_playAlbumBtn_clicked()
{
    switch (player->playbackState()) {
    case QMediaPlayer::StoppedState:
        playTrack(0);
        break;
    case QMediaPlayer::PlayingState:
        player->pause();
        break;
    case QMediaPlayer::PausedState:
        player->play();
        break;
    }
}

void EditorMain::on_playSongBtn_clicked()
{
    if (player->isPlaying())
        player->pause();
    else
        player->play();
}

void EditorMain::on_tableContextMenu(const QPoint &pos)
{
    QTableWidgetItem* item = ui->tracksTableWidget->itemAt(pos);
    QMenu menu(this);
    if (!item) { // clicked empty space
        QMenu* subMenu = menu.addMenu("Add");
        QAction* addTrackOption = subMenu->addAction("New Track");
        QAction* selected = menu.exec(ui->tracksTableWidget->viewport()->mapToGlobal(pos));
        if (selected == addTrackOption) {
            QStringList files = QFileDialog::getOpenFileNames(this, "Select Audio", "", "Audio Files (*.mp3 *.wav *.ogg *.flac)");
            for (const QString& file : std::as_const(files))
                handleAudio(file);
        }
        return;
    }

    QAction* renameAction = item->column() == 2 ? nullptr : menu.addAction("Rename");
    QAction* deleteAction = menu.addAction("Delete");

    QAction* selected = menu.exec(ui->tracksTableWidget->viewport()->mapToGlobal(pos));
    if (!selected)
        return;

    if (selected == renameAction) {
        ui->tracksTableWidget->editItem(item);
    } else if (selected == deleteAction) {
        ui->tracksTableWidget->removeRow(item->row());
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

void EditorMain::handleAudio(const QString& file)
{
    QFileInfo info(file);
    QString artistName = ui->artistName->text();
    int row = ui->tracksTableWidget->rowCount();

    ui->tracksTableWidget->insertRow(row);
    QTableWidgetItem* titleItem = new QTableWidgetItem();
    titleItem->setData(Qt::UserRole, file);
    ui->tracksTableWidget->setItem(row, 0, titleItem);
    ui->tracksTableWidget->setItem(row, 1, new QTableWidgetItem());
    ui->tracksTableWidget->setItem(row, 2, new QTableWidgetItem());

    QMediaPlayer* tempPlayer = new QMediaPlayer(this);
    QAudioOutput* tempAudio = new QAudioOutput(tempPlayer);
    tempPlayer->setAudioOutput(tempAudio);
    tempPlayer->setSource(QUrl::fromLocalFile(file));

    connect(tempPlayer, &QMediaPlayer::mediaStatusChanged, this, [this, tempPlayer, artistName, info, row](QMediaPlayer::MediaStatus status) {
        if (status != QMediaPlayer::LoadedMedia)
            return;

        QMediaMetaData meta = tempPlayer->metaData();
        qint64 duration = tempPlayer->duration();
        int seconds = duration / 1000, minutes = seconds / 60;
        seconds %= 60;
        QString durationText = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));

        QVariant title = meta.value(QMediaMetaData::Title);
        QString titleText = title.isNull() ? info.completeBaseName() : title.toString();

        QVariant artist = meta.value(QMediaMetaData::ContributingArtist);
        QString artistText = artist.isNull() ? artistName : artist.toString();

        ui->tracksTableWidget->item(row, 0)->setText(titleText);
        ui->tracksTableWidget->item(row, 1)->setText(artistText);
        auto durationItem = ui->tracksTableWidget->item(row, 2);
        durationItem->setText(durationText);
        durationItem->setFlags(durationItem->flags() & ~Qt::ItemIsEditable);
        tempPlayer->deleteLater();
    });
}

void EditorMain::trackPositionChanged(qint64 position)
{
    ui->trackProgressBar->setValue((position * 100) / player->duration());
    int seconds = position / 1000, minutes = seconds / 60;
    seconds %= 60;
    QString positionText = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));
    ui->songPositionTxt->setText(positionText);
}

void EditorMain::trackDurationChanged(qint64 duration)
{
    int seconds = duration / 1000, minutes = seconds / 60;
    seconds %= 60;
    QString durationText = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));
    ui->songDurationTxt->setText(durationText);
}

void EditorMain::trackStateChanged(QMediaPlayer::PlaybackState newState)
{
    switch (newState) {
    case QMediaPlayer::StoppedState:
        playNext(); // current track has finished playing, play the next one in the queue
        break;
    case QMediaPlayer::PlayingState:
        ui->mediaPlayerUI->show();
        ui->playSongBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        ui->playAlbumBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        break;
    case QMediaPlayer::PausedState:
        ui->playSongBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        ui->playAlbumBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
    }
}

void EditorMain::trackProgressBarValueEdited(int val)
{
    int position = (val / 100.0) * player->duration();
    player->setPosition(position);
    player->play();
}

void EditorMain::trackProgressBarMouseDragged(int)
{
    player->pause();
}

void EditorMain::on_TracksReordered()
{
    unshuffledTrackQueue.clear();
    for (int row = 0; row < ui->tracksTableWidget->rowCount(); row++) {
        const QString& path = ui->tracksTableWidget->item(row, 0)->data(Qt::UserRole).toString();
        unshuffledTrackQueue.emplaceFront(path, row);
    }
    trackQueue = unshuffledTrackQueue;
}