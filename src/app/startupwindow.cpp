#include "startupwindow.h"
#include "editormain.h"
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
    EditorMain* window = new EditorMain(this);
    window->show();
    this->hide();
}

