#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "lib/LibCircularBuffer/libcircularbuffer_1.h"
#include "helper.h"

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
};

#endif // VIDEOSTREAM_H
