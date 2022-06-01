#include "mustacheanimation.h"

MustacheAnimation::MustacheAnimation()
{
    this->matMustache = Helper::loadMatFromQrc(":/img/mustache.png");

    cascade = Helper::loadCascadeClassifierFromQrc(":/xml/xml/haarcascade_mcs_mouth.xml");
}

MustacheAnimation::~MustacheAnimation() { }

void MustacheAnimation::execute()
{
    if(!this->mat.empty())
    {
        // Based on :
        // - https://www.geeksforgeeks.org/opencv-c-program-face-detection/
        // - https://datahacker.rs/003-opencv-projects-how-to-create-instagram-like-filters-mustaches-glasses-and-masks/

        double scale = 1.0;

        std::vector<cv::Rect> mouths;

        // Frame variable (input)
        cv::Mat matFramegray, matFrameROI, matFrameSmall, matFrameMasked, matFrameWithMustacheMask;

        // Mustache variables
        cv::Mat matMustacheSmall, matMustacheSmallGray, matMustacheMask, matMustacheMaskInv;

        cvtColor(this->mat, matFramegray, cv::COLOR_BGR2GRAY); // Convert to Gray Scale
        double fx = 1 / scale;

        // Resize the Grayscale Image
        cv::resize(matFramegray, matFrameSmall, cv::Size(), fx, fx, cv::INTER_LINEAR);
        equalizeHist(matFrameSmall, matFrameSmall);

        // Detect faces of different sizes using cascade classifier
        cascade.detectMultiScale(matFrameSmall, mouths, 1.7, 11, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // Draw circles around the faces
        for (size_t i = 0; i < mouths.size(); i++)
        {
            cv::Rect roi = mouths[i];

            if (roi.height > 0 && roi.width > 0)
            {
                roi.height *= 2;
                roi.width *= 2;
                roi.y -= 20;
                roi.x -= roi.width/4;
                if(roi.x < 0) roi.x = 0;
            }

            if(0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= mat.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= mat.rows)
            {
                matFrameROI = this->mat(roi); // Extract Region Of Interest (mouth)

                // Resizing the image
                cv::resize(this->matMustache, matMustacheSmall, cv::Size(roi.width, roi.height), 0, 0, cv::INTER_AREA);

                // Convert image into grayscale
                cv::cvtColor(matMustacheSmall, matMustacheSmallGray, cv::COLOR_BGR2GRAY);

                cv::threshold(matMustacheSmallGray, matMustacheMask, 244, 255,  cv::THRESH_BINARY_INV);

                cv::bitwise_not(matMustacheMask, matMustacheMaskInv);

                cv::bitwise_and(matMustacheSmall, matMustacheSmall, matFrameWithMustacheMask, matMustacheMask);

                cv::bitwise_and(matFrameROI, matFrameROI, matFrameMasked, matMustacheMaskInv);

                cv::add(matFrameWithMustacheMask, matFrameMasked, this->mat(roi));
            }
        }
    }
}
