#include "facialblureffect.h"

FacialBlurEffect::FacialBlurEffect()
{

}

FacialBlurEffect::~FacialBlurEffect() { }

void FacialBlurEffect::execute()
{
    if(!this->mat.empty())
    {
        cv::CascadeClassifier cascade;
        double scale = 1.0;

        // Load classifiers from "opencv/data/haarcascades" directory
        cascade.load("C:/opencv-build/install/etc/haarcascades/haarcascade_frontalface_alt.xml");

        std::vector<cv::Rect> faces;
        cv::Mat gray, smallImg, output;

        cvtColor(this->mat, gray, cv::COLOR_BGR2GRAY); // Convert to Gray Scale
        double fx = 1 / scale;

        // Resize the Grayscale Image
        resize(gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR);
        equalizeHist(smallImg, smallImg);

        // Detect faces of different sizes using cascade classifier
        cascade.detectMultiScale(smallImg, faces, 1.7, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // Draw circles around the faces
        for (size_t i = 0; i < faces.size(); i++)
        {
            cv::Rect r = faces[i];
            cv::GaussianBlur(this->mat(r), this->mat(r), cv::Size(51, 51), 0);
        }
    }
}

