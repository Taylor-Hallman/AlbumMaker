#ifndef EDITORMAIN_H
#define EDITORMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSet>
#include <QPoint>
#include <QStack>

#include "../serialization/project.h"

namespace Ui {
class EditorMain;
}

class EditorMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorMain(QWidget *parent = nullptr);
    ~EditorMain();

public slots:
    void on_projectCreated(QString projectName, QString albumName, QString artistName, QString coverArtPaths, QVector<QString> trackPaths);
    void on_trackActivated(int row, int column);

private slots:
    void on_playAlbumBtn_clicked();

    void on_tableContextMenu(const QPoint& pos);

    void on_playSongBtn_clicked();
    void on_skipBackwardBtn_clicked();
    void on_skipForwardBtn_clicked();

    void on_shuffleBtn_clicked(bool checked);

    void on_shuffleBtn_Player_clicked(bool checked);


    void on_actionSave_triggered();

private:
    void playTrack(int trackIdx, bool keepFirst);
    void playNext();
    QSet<int> getSelectedRows();
    void handleAudio(const QString& file);
    void trackPositionChanged(qint64 position);
    void trackDurationChanged(qint64 duration);
    void trackStateChanged(QMediaPlayer::PlaybackState newState);
    void trackProgressBarValueEdited(int val);
    void trackProgressBarMouseDragged(int);
    void on_TracksReordered();
    void toggleShuffle(bool shuffle);
    void serializeToJson();

    QString coverArtPath;

    Ui::EditorMain *ui;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

    int nextTrackIdx = 0;
    int currTime = 0;

    QVector<int> trackQueue;

    QString projectPath = "";

signals:
    void sendProjectData(Project& p, QString path);
};

#endif // EDITORMAIN_H
