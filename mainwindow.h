#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void init();
    void createBtn();
    void deleteBtn();
    void changeColor();

private:
    Ui::MainWindow *ui;

    QVBoxLayout *vLayout = nullptr;
    QHBoxLayout *hLayout = nullptr;
    QDateTime dateTime;
    QPushButton *btnColor = nullptr;
};
#endif // MAINWINDOW_H
