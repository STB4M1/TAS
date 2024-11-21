#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , chart(new QChart())
    , series(new QLineSeries())
    , axisX(new QValueAxis())
    , axisY(new QValueAxis())
{
    ui->setupUi(this);
    setWindowTitle("TAS");

    // comboBoxPortNameにシリアルポートリストを追加
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        ui->comboBoxPortName->addItem(port.portName());
    }

    // 初期ウィンドウサイズを取得
    initialWindowSize = this->size();

    // すべての子ウィジェットの初期位置とサイズを保存
    const auto children = this->findChildren<QWidget*>();
    for (QWidget* widget : children) {
        initialGeometryMap[widget] = widget->geometry();
    }

    // widgetLvGraph の初期位置とサイズを保存
    initialGraphGeometry = ui->widgetLvGraph->geometry();

    // シリアルポートの設定
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readTemperatureData);

    // lineEditAveTemperature の文字を右揃えに設定
    ui->lineEditAveTemperature->setAlignment(Qt::AlignRight);

    // グラフの初期設定
    chart->addSeries(series);
    chart->legend()->hide(); // 凡例を非表示
    chart->setTitle("Temperature vs Time");

    // グラフの余白設定
    chart->setMargins(QMargins(0, 0, 0, 0)); // マージンを0に設定
    chart->setBackgroundRoundness(0); // 背景の角をなくす

    // X軸（経過時間）と Y軸（温度）の設定
    axisX->setTitleText("Time (s)");
    axisX->setLabelFormat("%.1f");
    axisX->setTickCount(10); // 必要に応じて調整
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setTitleText("Temperature (°C)");
        axisY->setLabelFormat("%.2f");
    axisY->setRange(0, 100); // Y軸の初期範囲
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // グラフを widgetLvGraph に最大限表示
    ui->widgetLvGraph->setChart(chart);
    ui->widgetLvGraph->setRenderHint(QPainter::Antialiasing);

    // widgetLvGraph の余白を調整（最大限表示のため）
    ui->widgetLvGraph->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // 現在のウィンドウサイズと初期サイズの比率を計算
    double widthRatio = static_cast<double>(width()) / initialWindowSize.width();
    double heightRatio = static_cast<double>(height()) / initialWindowSize.height();

    // 他のウィジェットの位置とサイズを比率に基づいて更新
    for (auto it = initialGeometryMap.begin(); it != initialGeometryMap.end(); ++it) {
        QWidget *widget = it.key();

        // widgetLvGraph は個別に管理するためスキップ
        if (widget == ui->widgetLvGraph) continue;

        QRect initialRect = it.value();
        int newX = static_cast<int>(initialRect.x() * widthRatio);
        int newY = static_cast<int>(initialRect.y() * heightRatio);
        int newWidth = static_cast<int>(initialRect.width() * widthRatio);
        int newHeight = static_cast<int>(initialRect.height() * heightRatio);

        widget->setGeometry(newX, newY, newWidth, newHeight);
    }

    // widgetLvGraph の位置とサイズを個別に更新
    int graphNewX = static_cast<int>(initialGraphGeometry.x() * widthRatio);
    int graphNewY = static_cast<int>(initialGraphGeometry.y() * heightRatio);
    int graphNewWidth = static_cast<int>(initialGraphGeometry.width() * widthRatio);
    int graphNewHeight = static_cast<int>(initialGraphGeometry.height() * heightRatio);
    ui->widgetLvGraph->setGeometry(graphNewX, graphNewY, graphNewWidth, graphNewHeight);
}


void MainWindow::readTemperatureData()
{
    while (serial->canReadLine()) {
        QString line = serial->readLine().trimmed();
        qDebug() << "Received data:" << line;

        QRegularExpression regex("([-+]?[0-9]*\\.?[0-9]+)");
        QRegularExpressionMatch match = regex.match(line);

        if (match.hasMatch()) {
            bool ok;
            double temperature = match.captured(1).toDouble(&ok);
            if (ok) {
                // キャリブレーション値の取得
                double calibrationValue = ui->lineEditCaliblationTemperature->text().toDouble(&ok);
                if (!ok) {
                    calibrationValue = 0.0; // 無効な入力は0として扱う
                }

                temperature += calibrationValue;
                QString formattedTemp = QString::number(temperature, 'f', 2);
                ui->lcdNumberLumiVal->display(formattedTemp);

                // ログ中の場合、データと記録時刻をリストに追加
                if (isLogging) {
                    QDateTime currentDateTime = QDateTime::currentDateTime(); // 記録時刻を取得
                    temperatureDataList.append(qMakePair(currentDateTime, temperature));

                    // グラフに追加 (経過時間を秒で計算)
                    qint64 elapsedSeconds = startTime.secsTo(currentDateTime);
                    series->append(elapsedSeconds, temperature);

                    // X軸の範囲を更新
                    axisX->setRange(0, elapsedSeconds);

                    // Y軸の範囲を 0 から temperature + 10 に動的に設定
                    double yMax = temperature + 10;
                    axisY->setRange(0, yMax);
                }
            } else {
                qDebug() << "Conversion to double failed for extracted data.";
            }
        } else {
            qDebug() << "No numeric data found in line:" << line;
        }
    }
}

void MainWindow::on_pushButtonLogStart_clicked()
{
    // comboBoxPortNameで選択されたポートを使用
    QString portName = ui->comboBoxPortName->currentText();
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open port" << portName;
        return;
    }
    qDebug() << "Serial port" << portName << "opened";

    // ログ開始
    isLogging = true;
    temperatureDataList.clear();
    series->clear();
    startTime = QDateTime::currentDateTime();
}


void MainWindow::on_pushButtonLogStop_clicked()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Serial port closed";
    }

    // ログ終了
    isLogging = false;

    // 記録した温度の平均値を計算
    if (!temperatureDataList.isEmpty()) {
        double sum = 0.0;
        for (const auto &data : temperatureDataList) {
            sum += data.second;
        }
        double average = sum / temperatureDataList.size();
        ui->lineEditAveTemperature->setText(QString::number(average, 'f', 2)); // 小数点第2位まで
    } else {
        ui->lineEditAveTemperature->setText("N/A"); // データがない場合
    }
}


void MainWindow::on_pushButtonOutputData_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Data"), "", tr("Dat Files (*.dat);;Text Files (*.txt);;CSV Files (*.csv)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // ファイルが開けなかった場合のエラー処理
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing"));
        return;
    }

    QTextStream out(&file);

    out << "Time, Temperature\n"; // データヘッダー行を追加

    for (const auto &data : temperatureDataList) {
        QDateTime timestamp = data.first;
        double temperature = data.second;
        out << timestamp.toString("yyyy-MM-dd hh:mm:ss") << ", " << QString::number(temperature, 'f', 2) << '\n';
    }

    file.close();
    qDebug() << "Data written to" << fileName;
}


MainWindow::~MainWindow()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete ui;
}
