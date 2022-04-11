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
    static cv::Mat transformMatWithKernel(cv::Mat src, cv::Mat_<float>);
    static cv::Mat transformMatWithKernel(cv::Mat src,
                                          float x0y0, float x1y0, float x2y0,
                                          float x0y1, float x1y1, float x2y1,
                                          float x0y2, float x1y2, float x2y2);
};

#endif // HELPER_H
