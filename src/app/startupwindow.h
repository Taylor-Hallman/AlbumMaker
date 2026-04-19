#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartupWindow;
}
QT_END_NAMESPACE

class StartupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartupWindow(QWidget *parent = nullptr);
    ~StartupWindow() override;

private slots:
    void on_actionNew_Project_triggered();
    void on_createdProject(QString, QString, QString, QString, QVector<QString>);

private:
    Ui::StartupWindow *ui;
};
#endif // STARTUPWINDOW_H
