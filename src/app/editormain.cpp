#include "editormain.h"
#include "ui_editormain.h"

EditorMain::EditorMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorMain)
{
    ui->setupUi(this);
    this->showMaximized();
}

EditorMain::~EditorMain()
{
    delete ui;
}

void EditorMain::on_projectCreated(QString coverArt, QVector<QString> tracks)
{

}
