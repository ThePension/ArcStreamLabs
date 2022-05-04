#include "imageprocessing.h"
#include <QDebug>
#include <iostream>

using namespace cv;
using namespace std;

ImageProcessing::ImageProcessing(CircularBuffer *circularBuffer, ActionManager * am, QObject * parent) : QThread(parent)
{
    this->circularBuffer = circularBuffer;
    this->actionManager = am;
}

ImageProcessing::~ImageProcessing() {}

void ImageProcessing::setKernel(cv::Mat kernel)
{
    this->kernel = kernel;
}

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

            if(!this->kernel.empty()) mGaussianBlur = Helper::transformMatWithKernel(mGaussianBlur, this->kernel);

            mGaussianBlur = this->actionManager->executeFilters(mGaussianBlur);

            mPixmap = Helper::cvMatToQPixmap(mGaussianBlur);

            emit imagedProcessed();
        }
    }
}

