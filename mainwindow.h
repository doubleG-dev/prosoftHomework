#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer * m_timerGenerator;
    QTimer * m_timerButtonMove;

private slots:

private:
    void init();

private:
    Ui::MainWindow *ui;
    QPushButton * m_snowFlakes;

};
#endif // MAINWINDOW_H
