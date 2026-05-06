#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QString>

#include "../serialization/project.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();

public slots:
    void on_ProjectDataReceived(Project& p, QString path);
private slots:

    void on_chooseDirBtn_clicked();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_nameField_textChanged(const QString &arg1);

    void on_pathField_textChanged(const QString &arg1);


private:
    Ui::SaveDialog *ui;

    Project project;

    void openFileDialog();
};

#endif // SAVEDIALOG_H
