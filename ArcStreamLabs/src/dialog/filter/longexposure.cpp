#include "longexposure.h"

#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>

LongExposure::LongExposure()
{

}

LongExposure::~LongExposure()
{

}

void LongExposure::execute()
{
    if(!this->mat.empty())
    {
        // based on : https://docs.opencv.org/3.4/d3/d94/samples_2cpp_2tutorial_code_2ImgTrans_2Sobel_Demo_8cpp-example.html#a16
        cv::Mat imA, imB, imC, imD, output;
        std::vector<cv::Mat> images;
        double alpha = 0.8; double beta, gamma=0.5;

        //utiliser un combobox pour choisir
       imB = Helper::loadMatFromQrc(":/img/asianGhost.png");
       imC = Helper::loadMatFromQrc(":/img/Boloss.png");
       imD = Helper::loadMatFromQrc(":/img/asianBoloss.png");

        beta = ( 1.0 - alpha );
        addWeighted( this->mat, alpha, imD, beta, 0.0, output);

        this->mat = output;
    }
}
