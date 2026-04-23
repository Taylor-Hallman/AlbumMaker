#include "startupwindow.h"
#include "createprojectdialog.h"
#include "ui_startupwindow.h"
#include "editormain.h"

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

// Debug option to make testing easier; delete this in final build
void StartupWindow::on_actionExample_Project_triggered()
{
    QString coverArtPath = "/home/taylor/Pictures/LightTrick_AlbumArt.png";
    QVector<QString> trackPaths =
    {
        "/home/taylor/Music/A Man Stands in the Mirror.wav",
        "/home/taylor/Music/Bluest Smile.wav",
        "/home/taylor/Music/Bright Star.wav",
        "/home/taylor/Music/It's All Right Now.wav",
        "/home/taylor/Music/River House.wav",
        "/home/taylor/Music/She Goes Out.wav",
        "/home/taylor/Music/Waterline.wav"
    };
    EditorMain* editor = new EditorMain();
    editor->show();
    editor->on_projectCreated("Light Trick", "Light Trick", "Mark Hallman", coverArtPath, trackPaths);
    this->close();
}

