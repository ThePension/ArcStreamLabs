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
                mPixmap = Helper::cvMatToQPixmap(mFrame);
                emit newPixmapCaptured();
            }
        }
    }
}
