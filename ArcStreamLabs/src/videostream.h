#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include "opencv2/opencv.hpp"

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

protected:
    void run() override;
signals:
    void newPixmapCaptured();
private:
    QPixmap mPixmap;
    cv::Mat mFrame;
    cv::VideoCapture mVideoCap;
    // https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    QImage cvMatToQImage( const cv::Mat &inMat );
};

#endif // VIDEOSTREAM_H
