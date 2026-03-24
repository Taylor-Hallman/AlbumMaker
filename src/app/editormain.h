#ifndef EDITORMAIN_H
#define EDITORMAIN_H

#include <QMainWindow>

namespace Ui {
class EditorMain;
}

class EditorMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorMain(QWidget *parent = nullptr);
    ~EditorMain();

private:
    Ui::EditorMain *ui;
};

#endif // EDITORMAIN_H
