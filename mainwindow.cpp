#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete vLayout;
    delete hLayout;
    delete ui;
}

void MainWindow::init()
{
    QPushButton *btnTime = new QPushButton("Время");
    QPushButton *btnCreate = new QPushButton("Создать");
    QPushButton *btnDelete = new QPushButton("Удалить");

    vLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();


    hLayout->addWidget(btnCreate);
    hLayout->addWidget(btnDelete);

    hLayout->setSizeConstraint(QLayout::SetMinimumSize);

    vLayout->addWidget(btnTime);
    vLayout->addLayout(hLayout);

    vLayout->setSizeConstraint(QLayout::SetMinimumSize);

    centralWidget()->setLayout(vLayout);

    resize(hLayout->minimumSize());

    connect(btnTime, &QPushButton::clicked, this,[this](){
        qDebug() << dateTime.currentDateTime().toString("dd.MM HH:mm:ss");
    });


    connect(btnCreate, &QPushButton::clicked, this, &MainWindow::createBtn);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::deleteBtn);
}

void MainWindow::createBtn()
{
    if(btnColor != nullptr)
        return;

    QString color = QColor(qrand()%255, qrand()%255, qrand()%255).name(QColor::NameFormat::HexRgb);

    QString btnStyle = QString("background-color: %1;").arg(color);

    btnColor = new QPushButton(this);
    btnColor->setText(color);
    btnColor->setStyleSheet(btnStyle);
    vLayout->addWidget(btnColor);

    connect(btnColor, &QPushButton::clicked, this, &MainWindow::changeColor);
}

void MainWindow::deleteBtn()
{
    if(btnColor == nullptr)
        return;

    disconnect(btnColor, &QPushButton::clicked, this, &MainWindow::changeColor);
    delete btnColor;
    btnColor = nullptr;
}

void MainWindow::changeColor()
{
    QString color = QColor(qrand()%255, qrand()%255, qrand()%255).name(QColor::NameFormat::HexRgb);
    QString btnStyle = QString("background-color: %1;").arg(color);
    btnColor->setText(color);
    btnColor->setStyleSheet(btnStyle);
}



