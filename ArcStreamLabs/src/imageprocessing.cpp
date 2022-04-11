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
            mPixmap = Helper::cvMatToQPixmap(mGaussianBlur);
            emit imagedProcessed();   

        }
    }
}
