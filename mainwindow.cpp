#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QDateTime>
#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //UI初始化区
    //设置背景图 后期去除边框(测试时加) 版本自动更新
    //this->setStyleSheet("background:gray");
    this->setStyleSheet("#MainWindow{border-image:url(:/new/prefix1/800480.jpg);}");

    ui->weatherLabel1->setFrameShape (QFrame::Box);
    ui->weatherLabel2->setFrameShape (QFrame::Box);
    ui->weatherLabel3->setFrameShape (QFrame::Box);

    //ui->videoWidget->setFrameShape (QFrame::Box);//出错

    //logo二维码区域如何只显示80大小 剩余自己发挥 不拉伸
    ui->logoLabel->setFrameShape (QFrame::Box);//设置边框
    ui->logoLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix2/80.jpg);}");

    //"紧急消息"加粗变黑 内容红色
    newsCurIndex = 0;//当前角码
    jinjiNews = "紧急消息,项目要提前交啦!再不做完就拜拜啦123456789123546798";
    newsWidth = fontMetrics().width("a");//每个字符宽度
    ui->jinjiNewLabel->setFrameShape (QFrame::Box);
    ui->jinjiNewLabel->setMinimumHeight(40);
    ui->jinjiNewLabel->setMaximumWidth(580);
    //触发滚动消息
    timerNews = new QTimer;
    connect(timerNews, &QTimer::timeout, this, &MainWindow::updateIndex);
    timerNews->start(200);

    ui->activityLabel->setFrameShape (QFrame::Box);
    ui->newLabel->setFrameShape (QFrame::Box);

    //定时器
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTime()));
    timer->start(1000);//更新显示时间间隔

    //功能初始化区
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_data()));
    socket->connectToHost("192.168.1.105",9876);//连接时机 地址更改使用
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_data()
{
    //接收服务器发来的信息
    QString msg=socket->readAll();
    //ui->listWidget->addItem(msg);
    qDebug()<<msg;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //__super::paintEvent(event);
    QPainter painter(this);//750, 435
    //painter.drawText(201, 460, jinjiNews.mid(0));//newsCurIndex
    painter.drawText(width() - newsWidth*newsCurIndex, 460, jinjiNews.left(jinjiNews.length()));//newsCurIndex 10秒左右显示一次
}


void MainWindow::updateIndex()
{
    update();
    newsCurIndex++;
    if (newsCurIndex*newsWidth > width())
        newsCurIndex = 0;
}

void MainWindow::timerTime()//显示时间 有延时如何解决
{
    QDateTime sysTime = QDateTime::currentDateTime();
    ui->timeLabel->setFrameShape (QFrame::Box);
    ui->timeLabel->setText(sysTime.toString("yyyy-MM-dd hh:mm:ss dddd"));
}
