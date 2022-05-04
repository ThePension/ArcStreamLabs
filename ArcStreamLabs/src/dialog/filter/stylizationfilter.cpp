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

        stylization(this->mat, output, 60, 0.45f);

        this->mat = output;
    }
}
