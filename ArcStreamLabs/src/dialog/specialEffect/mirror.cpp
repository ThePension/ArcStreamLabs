#include "mirror.h"

Mirror::Mirror()
{

}

Mirror::~Mirror()
{

}

void Mirror::execute()
{
    if(!this->mat.empty())
    {
        cv::Mat output;

        cv::flip(this->mat, output, 1);

        this->mat = output;
    }
}
