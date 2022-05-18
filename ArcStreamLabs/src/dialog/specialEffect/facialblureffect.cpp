#include "facialblureffect.h"

FacialBlurEffect::FacialBlurEffect()
{
    // Load classifiers from "opencv/data/haarcascades" directory
    if(Helper::doesFolderExists("C:/opencv/release"))
    {
        cascadeFrontalFace.load("C:/opencv/release/install/etc/haarcascades/haarcascade_frontalface_default.xml");
        cascadeProfileFace.load("C:/opencv/release/install/etc/haarcascades/haarcascade_profileface.xml");
    }
    else if (Helper::doesFolderExists("C:/opencv-build"))
    {
        cascadeFrontalFace.load("C:/opencv-build/install/etc/haarcascades/haarcascade_frontalface_default.xml");
        cascadeProfileFace.load("C:/opencv-build/install/etc/haarcascades/haarcascade_profileface.xml");
    }
}

FacialBlurEffect::~FacialBlurEffect() { }

void FacialBlurEffect::execute()
{
    if(!this->mat.empty())
    {
        double scale = 1.0;

        std::vector<cv::Rect> frontalFaces, rightProfileFaces, leftProfileFaces;
        cv::Mat matFrameGray, matFrameGraySmall, matFrameGraySmallFlipped;

        cvtColor(this->mat, matFrameGray, cv::COLOR_BGR2GRAY); // Convert to Gray Scale
        double fx = 1 / scale;

        // Resize the Grayscale Image
        resize(matFrameGray, matFrameGraySmall, cv::Size(), fx, fx, cv::INTER_LINEAR);
        equalizeHist(matFrameGraySmall, matFrameGraySmall);

        int w = matFrameGraySmall.size().width;

        // Flip the image
        cv::flip(matFrameGraySmall, matFrameGraySmallFlipped, 1);

        double scaleFactor = 1.7; // To Tweak to improve perf.

        // Detect faces of different sizes using cascade classifier
        cascadeFrontalFace.detectMultiScale(matFrameGraySmall, frontalFaces, scaleFactor);

        // Detect profile face from the right
        //cascadeProfileFace.detectMultiScale(matFrameGraySmall, rightProfileFaces, scaleFactor);

        // Detect profile face from the left
        //cascadeProfileFace.detectMultiScale(matFrameGraySmallFlipped, leftProfileFaces, scaleFactor);


        // Blur the frontal faces
        for (size_t i = 0; i < frontalFaces.size(); i++)
        {
            cv::Rect r = frontalFaces[i];
            cv::GaussianBlur(this->mat(r), this->mat(r), cv::Size(51, 51), 0);
        }

        // Blur the profile faces from the right
        for (size_t i = 0; i < rightProfileFaces.size(); i++)
        {
            cv::Rect r = rightProfileFaces[i];
            cv::GaussianBlur(this->mat(r), this->mat(r), cv::Size(51, 51), 0);
        }

        // Blur the profile faces from the left
        for (size_t i = 0; i < leftProfileFaces.size(); i++)
        {
            cv::Rect r = leftProfileFaces[i];

            int dec = 2 * ((w / 2) - (r.x + r.width)) + r.width;

            // Flip the ROI
            r.x += dec;

            cv::GaussianBlur(this->mat(r), this->mat(r), cv::Size(51, 51), 0);
        }
    }
}

