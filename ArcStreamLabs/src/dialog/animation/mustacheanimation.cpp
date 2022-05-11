#include "mustacheanimation.h"

MustacheAnimation::MustacheAnimation()
{
    // this->matMustache = cv::imread(":/img/mustache.png");

    // Load classifiers from "opencv/data/haarcascades" directory
    cascade.load("C:/opencv-build/install/etc/haarcascades/haarcascade_mcs_mouth.xml");
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

        std::vector<cv::Rect> faces;
        cv::Mat gray, smallImg, output;

        cvtColor(this->mat, gray, cv::COLOR_BGR2GRAY); // Convert to Gray Scale
        double fx = 1 / scale;

        // Resize the Grayscale Image
        resize(gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR);
        equalizeHist(smallImg, smallImg);

        // Detect faces of different sizes using cascade classifier
        cascade.detectMultiScale( smallImg, faces, 1.7, 11, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // Draw circles around the faces
        for (size_t i = 0; i < faces.size(); i++)
        {
            cv::Rect r = faces[i];
            cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing tool

            cv::rectangle(this->mat,
                      cv::Point(cvRound(r.x*scale),
                      cvRound(r.y*scale)),
                      cv::Point(cvRound((r.x + r.width-1)*scale),
                      cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
        }
    }
}
