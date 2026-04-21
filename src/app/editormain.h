#ifndef EDITORMAIN_H
#define EDITORMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSet>
#include <QPoint>
#include <QMouseEvent>

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
private:
    void playTrack(int trackIdx);
    QSet<int> getSelectedRows();
    void handleAudio(const QString& file);
    void trackPositionChanged(qint64 position);
    void trackDurationChanged(qint64 duration);
    void trackProgressBarValueEdited(int val);
    void trackProgressBarMouseDragged(int);

    QString coverArtPath;

    Ui::EditorMain *ui;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

    bool isPlaying = false;
    int currTrackIdx;
    int currTime = 0;
};

#endif // EDITORMAIN_H
