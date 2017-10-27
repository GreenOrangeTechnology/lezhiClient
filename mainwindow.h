#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void updateIndex();
private:
    Ui::MainWindow *ui;
    const QString version="0.0.0";//app自动更新依据字段
    QTimer *timer;//更新时间 图片 消息
    QTimer *timerNews;//更新消息

    QString jinjiNews;
    int newsWidth;//每个字符宽度
    int newsCurIndex;//角码

    QTcpSocket *socket;
private slots:
    void timerTime();
    void read_data();
};

#endif // MAINWINDOW_H
