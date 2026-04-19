#include "startupwindow.h"
#include "createprojectdialog.h"
#include "ui_startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartupWindow)
{
    ui->setupUi(this);
}

StartupWindow::~StartupWindow()
{
    delete ui;
}

void StartupWindow::on_actionNew_Project_triggered()
{
    CreateProjectDialog* dialog = new CreateProjectDialog();
    QObject::connect(dialog, &CreateProjectDialog::createdProject, this, &StartupWindow::on_createdProject);
    dialog->show();
}

void StartupWindow::on_createdProject(QString, QString, QString, QString, QVector<QString>) {
    this->close();
}

