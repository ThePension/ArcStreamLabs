#ifndef HELPER_H
#define HELPER_H
#include "opencv2/opencv.hpp"
#include <QImage>
#include <QPixmap>
#include <QDebug>

class Helper
{
public:
    Helper();

    // https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
    static QPixmap cvMatToQPixmap(const cv::Mat &inMat);
    static QImage cvMatToQImage(const cv::Mat &inMat);
};

#endif // HELPER_H
