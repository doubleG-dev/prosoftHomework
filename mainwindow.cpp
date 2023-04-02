#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_timerGenerator(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    connect(m_timerGenerator, &QTimer::timeout, this, [this]{
        m_snowFlakes = new QPushButton("*",this);
        m_snowFlakes->installEventFilter(this);
        m_snowFlakes->setMouseTracking(true);

        m_timerButtonMove = new QTimer(this);

        auto btnMove = [btnSnowFlake = this->m_snowFlakes]{
            if(btnSnowFlake->underMouse())
                btnSnowFlake->move(btnSnowFlake->pos().rx(),
                               btnSnowFlake->pos().ry() + QRandomGenerator::global()->bounded(5,10));
            else if(!btnSnowFlake->underMouse())
                btnSnowFlake->move(btnSnowFlake->pos().rx(),
                               btnSnowFlake->pos().ry() + QRandomGenerator::global()->bounded(5));
        };

        auto loseGame = [btnSnowFlake = this->m_snowFlakes, this]{
            if(btnSnowFlake->pos().ry() > (this->height() - btnSnowFlake->height()))
            {
                QPalette pal = this->palette();
                pal.setColor(QPalette::Window , Qt::red);
                this->setPalette(pal);
                this->setWindowTitle("YOU LOOSE!!!");
            }
        };

        auto btnDelete = [btnSnowFlake = this->m_snowFlakes, stopTimer = this->m_timerButtonMove]{
            stopTimer->deleteLater();
            btnSnowFlake->deleteLater();
        };

        connect(m_snowFlakes, &QPushButton::clicked, this, btnDelete);
        connect(m_timerButtonMove, &QTimer::timeout, this, loseGame);
        connect(m_timerButtonMove, &QTimer::timeout, this, btnMove);


        m_snowFlakes->resize(20,20);
        m_snowFlakes->move(QRandomGenerator::global()->bounded(0,width() - m_snowFlakes->width()),
                           QRandomGenerator::global()->bounded(0,100));


        int randomTime = QRandomGenerator::global()->bounded(100,1000);
        m_timerGenerator->start(randomTime);
        m_timerButtonMove->start(100);


        m_snowFlakes->show();
    });

    this->setWindowTitle("Snow Flakes");
    int randomTime = QRandomGenerator::global()->bounded(100,1000);
    m_timerGenerator->start(randomTime);
}
