#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class Launcher;
}

class Launcher : public QWidget
{
    Q_OBJECT

public:
    explicit Launcher(QWidget *parent = 0);
    ~Launcher();

private slots:
    void on_pushButton_clicked();
    void on_gameButton_clicked();
    void on_mapEditorButton_clicked();

private:
    Ui::Launcher *ui;
    QMainWindow *window;
};

#endif // LAUNCHER_H
