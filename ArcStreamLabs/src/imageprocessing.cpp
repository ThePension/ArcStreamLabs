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
<<<<<<< HEAD

            for ( int i = 1; i < /*valeur a modifié pour la netteté :man_shrugging*/3; i = i + 2 )
            {
                GaussianBlur(mFrame, mGaussianBlur, Size(i,i), 0, 0, BORDER_DEFAULT);
            }
            mPixmap = Helper::cvMatToQPixmap(mGaussianBlur);
            emit imagedProcessed();   

=======
            mFrame = sepiaFilter(mFrame);
            mPixmap = Helper::cvMatToQPixmap(mFrame);
            emit imagedProcessed();
>>>>>>> 6294485 (Adding sepia filter with kernel transform + Generic kernel transform)
        }
    }
}

Mat ImageProcessing::sepiaFilter(Mat src)
{
    // Based on : https://amin-ahmadi.com/2016/03/24/sepia-filter-opencv/
    Mat kernel = (Mat_<float>(3, 3)
                    << 0.272, 0.534, 0.131,
                       0.349, 0.686, 0.168,
                       0.393, 0.769, 0.189);

    return Helper::transformMatWithKernel(src, kernel);
}
