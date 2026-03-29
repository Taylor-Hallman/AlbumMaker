#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>

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

private:
    Ui::CreateProjectDialog *ui;

signals:
    void createdProject();
};

#endif // CREATEPROJECTDIALOG_H
