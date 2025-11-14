#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort> // シリアル通信のためのヘッダーを追加
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QList>
#include <QPair>
#include <QDateTime>
#include <QFile>
#include <QDateTime>
#include <QMap>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLogStart_clicked();
    void on_pushButtonLogStop_clicked();
    void on_pushButtonOutputData_clicked();
    void readTemperatureData(); // データ受信用のスロット
//    void on_comboBoxPortName_currentIndexChanged(const QString &portName);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial; // シリアルポートのメンバー変数
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QList<QPair<QDateTime, double>> temperatureDataList; // 時間と温度データを格納するリスト
    bool isLogging = false; // ログ状態を確認するフラグ
    QDateTime startTime; // 記録開始時刻
    QMap<QWidget*, QRect> initialGeometryMap; // すべてのウィジェットの初期位置とサイズ
    QRect initialGraphGeometry; // widgetLvGraph の初期位置とサイズ
    QSize initialWindowSize; // 初期の MainWindow サイズ

protected:
    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
