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
    delete ui;
}

void MainWindow::init()
{
    QPushButton *btnTime = new QPushButton("Время",this);
    QPushButton *btnCreate = new QPushButton("Создать",this);
    QPushButton *btnDelete = new QPushButton("Удалить",this);

    m_vLayout = new QVBoxLayout(this);
    m_hLayout = new QHBoxLayout(this);


    m_hLayout->addWidget(btnCreate);
    m_hLayout->addWidget(btnDelete);

    m_vLayout->addWidget(btnTime);
    m_vLayout->addLayout(m_hLayout);

    centralWidget()->setLayout(m_vLayout);

    resize(m_hLayout->minimumSize());

    connect(btnTime, &QPushButton::clicked, this, [this]{
        qDebug() << m_dateTime.currentDateTime().toString("dd.MM HH:mm:ss");
    });


    connect(btnCreate, &QPushButton::clicked, this, &MainWindow::createBtn);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::deleteBtn);
}

void MainWindow::createBtn()
{
    if(m_btnColor != nullptr)
        return;

    QString color = QColor(qrand()%255, qrand()%255, qrand()%255).name(QColor::NameFormat::HexRgb);

    QString btnStyle = QString("background-color: %1;").arg(color);

    m_btnColor = new QPushButton(this);
    m_btnColor->setText(color);
    m_btnColor->setStyleSheet(btnStyle);
    m_vLayout->addWidget(m_btnColor);

    connect(m_btnColor, &QPushButton::clicked, this, &MainWindow::changeColor);
}

void MainWindow::deleteBtn()
{
    if(m_btnColor == nullptr)
        return;

    disconnect(m_btnColor, &QPushButton::clicked, this, &MainWindow::changeColor);
    delete m_btnColor;
    m_btnColor = nullptr;
}

void MainWindow::changeColor()
{
    QString color = QColor(qrand()%255, qrand()%255, qrand()%255).name(QColor::NameFormat::HexRgb);
    QString btnStyle = QString("background-color: %1;").arg(color);
    m_btnColor->setText(color);
    m_btnColor->setStyleSheet(btnStyle);
}
