#include "imageprocessing.h"
#include <QDebug>
#include <iostream>

using namespace cv;
using namespace std;

ImageProcessing::ImageProcessing(ArcStreamLabs::LibCircularBuffer::CircularBuffer *circularBuffer, QObject * parent) : QThread(parent)
{
    this->circularBuffer = circularBuffer;
}

ImageProcessing::~ImageProcessing() {}

void ImageProcessing::run()
{
    while(true)
    {
        if(circularBuffer->empty()==false)
        {
            mFrame = circularBuffer->read();
            for ( int i = 1; i < /*valeur a modifié pour la netteté :man_shrugging*/3; i = i + 2 )
            {
                GaussianBlur(mFrame, mGaussianBlur, Size(i,i), 0, 0, BORDER_DEFAULT);
            }
            mPixmap = cvMatToQPixmap(mGaussianBlur);
            emit imagedProcessed();   
        }
    }
}

QPixmap ImageProcessing::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

QImage ImageProcessing::cvMatToQImage(const cv::Mat &inMat)
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
