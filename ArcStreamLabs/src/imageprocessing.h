#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "lib/LibCircularBuffer/libcircularbuffer_1.h"
#include "helper.h"
#include "undo_redo/actionmanager.h"

#define ID_CAMERA 0

class ImageProcessing : public QThread
{
    Q_OBJECT
public:
    ImageProcessing(CircularBuffer *circularBuffer, ActionManager * am, QObject * parent = nullptr);
    ~ImageProcessing();

    QPixmap pixmap() const {
        return mPixmap;
    }

    void setKernel(cv::Mat);

protected:
    void run() override;
signals:
    void imagedProcessed();
private:
    CircularBuffer *circularBuffer;
    QPixmap mPixmap;
    cv::Mat mFrame, mGaussianBlur;
    cv::Mat kernel;
    ActionManager * actionManager;
};

#endif // VIDEOSTREAM_H
