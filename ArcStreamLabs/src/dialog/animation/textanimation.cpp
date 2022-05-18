#include "textanimation.h"


TextAnimation::TextAnimation(QString text)
{
    this->text = text;

    this->h = 0;
    this->w = 0;

    this->x = rand()%300;
    this->y = rand()%300;

    this->xspeed = 4.5;
    this->yspeed = 4.5;
}

TextAnimation::~TextAnimation() { }

void TextAnimation::execute()
{
    if(!this->mat.empty())
    {
        this->w = this->mat.size().width;
        this->h  =this->mat.size().height;

        cv::Point position = getNewPosition();
        cv::putText(this->mat, this->text.toStdString(), position, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
    }
}

void TextAnimation::moveCheck()
{
    if(this->x >= this->w)
    {
        xspeed = -xspeed;
    }
    if(this->x <= 0)
    {
        xspeed = -xspeed;
    }
    if(this->y >= this->h)
    {
        yspeed = -yspeed;
    }
    if(this->y <= 0)
    {
        yspeed = -yspeed;
    }
}

cv::Point TextAnimation::getNewPosition()
{
    this->x += this->xspeed;
    this->y += this->yspeed;

    moveCheck();

    return cv::Point(this->x, this->y);
}
