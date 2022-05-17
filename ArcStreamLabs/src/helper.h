#pragma once

#include "opencv2/opencv.hpp"
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include <QIODevice>

class Helper
{
public:
    Helper();

    // https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
    static QPixmap cvMatToQPixmap(const cv::Mat &inMat);
    static QImage cvMatToQImage(const cv::Mat &inMat);
    static cv::Mat transformMatWithKernel(cv::Mat src, cv::Mat_<float>);
    static cv::Mat transformMatWithKernel(cv::Mat src,
                                          float x0y0, float x1y0, float x2y0,
                                          float x0y1, float x1y1, float x2y1,
                                          float x0y2, float x1y2, float x2y2);
    static cv::Mat loadMatFromQrc(QString qrc, int flag = cv::IMREAD_COLOR);
    static bool doesFolderExists(QString folderPath);
};
