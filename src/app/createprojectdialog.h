#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QVector>

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();

private slots:
    void on_cancelBtn_clicked();

    void on_nextBtn_clicked();

    void on_nameField_textEdited(const QString &arg1);

    void on_browseBtn_clicked();

    void on_imageDropped(const QString& path);

    void on_audioDropped(const QString& path);

    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_downBtn_clicked();

    void on_upBtn_clicked();

    void on_tracksTable_itemSelectionChanged();

    void on_nameField_textChanged(const QString &arg1);

    void on_albumNameField_textChanged(const QString &arg1);

    void on_artistField_textChanged(const QString &arg1);

private:
    Ui::CreateProjectDialog *ui;
    QString coverArt;
    QVector<QString> tracks;
    QString projectName, albumName, artistName;

    void handleImage(const QString& path);
    void handleAudio(const QString& path);
    QSet<int> getSelectedRows();

signals:
    void createdProject(QString projectName, QString albumName, QString artistName, QString coverArt, QVector<QString> tracks);
};

#endif // CREATEPROJECTDIALOG_H
