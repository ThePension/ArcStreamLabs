#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "lib/LibCircularBuffer/libcircularbuffer_1.h"

#define ID_CAMERA 0

class ImageProcessing : public QThread
{
    Q_OBJECT
public:
    ImageProcessing(ArcStreamLabs::LibCircularBuffer::CircularBuffer *circularBuffer, QObject * parent = nullptr);
    ~ImageProcessing();

    QPixmap pixmap() const {
        return mPixmap;
    }

protected:
    void run() override;
signals:
    void imagedProcessed();
private:
    ArcStreamLabs::LibCircularBuffer::CircularBuffer *circularBuffer;
    QPixmap mPixmap;
    cv::Mat mFrame,mGaussianBlur;
    // https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    QImage cvMatToQImage( const cv::Mat &inMat );
};

#endif // VIDEOSTREAM_H
