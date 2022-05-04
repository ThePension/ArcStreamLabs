#include "sobelfilter.h"

SobelFilter::SobelFilter()
{

}

SobelFilter::~SobelFilter()
{

}

void SobelFilter::execute()
{
    if(!this->mat.empty())
    {
        cv::Mat grad_x, grad_y, output;
        cv::Mat abs_grad_x, abs_grad_y;

        int ddepth = CV_16S;
        int ksize = 3;
        int delta = 30;
        int scale = 1;

        Sobel(this->mat, grad_x, ddepth, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);

        Sobel(this->mat, grad_y, ddepth, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);

        // converting back to CV_8U
        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);

        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, output);

        this->mat = output;
    }
}
