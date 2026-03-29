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
    CreateProjectDialog* dialog = new CreateProjectDialog(this);
    dialog->show();
}

