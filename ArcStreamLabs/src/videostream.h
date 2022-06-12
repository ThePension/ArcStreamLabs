#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "helper.h"

#define ID_CAMERA 0

class VideoStream : public QThread
{
    Q_OBJECT
public:
    VideoStream(QObject * parent = nullptr);
    ~VideoStream();

    QPixmap pixmap() const {
        return mPixmap;
    }

    cv::Mat frame() const {
        return mFrame;
    }

protected:
    void run() override;
signals:
    void newPixmapCaptured();
private:
    QPixmap mPixmap;
    cv::Mat mFrame;
    cv::VideoCapture mVideoCap;
};

#endif // VIDEOSTREAM_H
