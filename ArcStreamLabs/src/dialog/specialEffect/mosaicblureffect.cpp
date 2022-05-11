#include "mosaicblureffect.h"

MosaicBlurEffect::MosaicBlurEffect()
{
    this->mat = cv::Mat();
    this->tileSize = 16;
}

MosaicBlurEffect::~MosaicBlurEffect() { }

void MosaicBlurEffect::execute()
{
    if(!this->mat.empty())
    {
        // Based on : https://stackoverflow.com/questions/55508615/how-to-pixelate-image-using-opencv-in-python

        int matWidth = this->mat.size().width;
        int matHeight = this->mat.size().height;

        int cols = matWidth / this->tileSize;
        int rows = matHeight / this->tileSize;

        cv::Mat temp, output;

        cv::resize(this->mat, temp, cv::Size(cols, rows), 0, 0, cv::INTER_LINEAR);

        cv::resize(temp, output, cv::Size(matWidth, matHeight), 0, 0, cv::INTER_NEAREST);

        this->mat = output;
    }
}

void MosaicBlurEffect::setTileSize(int tileSize)
{
    this->tileSize = tileSize;
}
