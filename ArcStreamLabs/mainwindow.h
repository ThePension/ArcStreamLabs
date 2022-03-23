#pragma once

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QMutex>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        QMutex mutex;
        Ui::MainWindow *ui;
        cv::Mat mat;

        void configureUI();
};
