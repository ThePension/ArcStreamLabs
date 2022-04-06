#include "videostream.h"
#include <QDebug>
#include <iostream>

using namespace cv;
using namespace std;

VideoStream::VideoStream(QObject * parent) : QThread(parent)
{
    mVideoCap = cv::VideoCapture(ID_CAMERA);
}

VideoStream::~VideoStream(){ }

/*!
 * \brief VideoStream::run
 */
void VideoStream::run()
{
    if(mVideoCap.isOpened())
    {
        while(true){
            mVideoCap >> mFrame;
            cv::flip(mFrame, mFrame, 1); // FLIP THE IMAGE (VERTICALLY)
            if(!mFrame.empty()){
                mPixmap = cvMatToQPixmap(mFrame);
                emit newPixmapCaptured();
            }
        }
    }
}

QPixmap VideoStream::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

QImage VideoStream::cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type())
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_ARGB32);

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_RGB888);

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_Grayscale8);

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}
