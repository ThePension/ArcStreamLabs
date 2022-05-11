#include "mosaicblureffect.h"

MosaicBlurEffect::MosaicBlurEffect() {
    this->mat = cv::Mat();
}

MosaicBlurEffect::~MosaicBlurEffect() { }

void MosaicBlurEffect::execute()
{
    if(!this->mat.empty())
    {
        // Based on : https://stackoverflow.com/questions/55508615/how-to-pixelate-image-using-opencv-in-python

        int tileSize = 16; // SHOULD BE A SLIDER

        int matWidth = this->mat.size().width;
        int matHeight = this->mat.size().height;

        int cols = matWidth / tileSize;
        int rows = matHeight / tileSize;

        cv::Mat temp, output;

        cv::resize(this->mat, temp, cv::Size(cols, rows), 0, 0, cv::INTER_LINEAR);

        cv::resize(temp, output, cv::Size(matWidth, matHeight), 0, 0, cv::INTER_NEAREST);

        this->mat = output;
    }
}
