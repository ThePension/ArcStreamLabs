#pragma once

#include "animationactions.h"

#include "opencv2/objdetect.hpp"
#include "../../helper.h"

class MustacheAnimation : public AnimationActions
{
private:
    cv::Mat matMustache;
    cv::CascadeClassifier cascade;

public:
    MustacheAnimation();
    virtual ~MustacheAnimation() override;

    void execute() override;
    void undo() override { }
};

