#include "stylizationfilter.h"

StylizationFilter::StylizationFilter()
{

}

StylizationFilter::~StylizationFilter()
{

}

void StylizationFilter::execute()
{
    if(!this->mat.empty())
    {
        // based on : https://learnopencv.com/non-photorealistic-rendering-using-opencv-python-c/
        cv::Mat output;

        stylization(this->mat, output, 1, 0.45f); // TODO : Add sliders for these values

        this->mat = output;
    }
}
