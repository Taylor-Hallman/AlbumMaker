#ifndef EDITORMAIN_H
#define EDITORMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSet>

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
    void on_projectCreated(QString projectName, QString albumName, QString artistName, QString coverArtPaths, QVector<std::pair<QString, QString>> trackPaths);
    void on_trackActivated(int row, int column);

private slots:
    void on_playAlbumBtn_clicked();

    void on_playBtn_clicked();

private:
    void playTrack(int trackIdx);
    QSet<int> getSelectedRows();

    Ui::EditorMain *ui;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

    bool isPlaying = false;
};

#endif // EDITORMAIN_H
