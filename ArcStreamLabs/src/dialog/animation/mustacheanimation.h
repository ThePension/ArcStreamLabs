#pragma once

#include "animationactions.h"

#include "opencv2/objdetect.hpp"

class MustacheAnimation : public AnimationActions
{
private:
    cv::Mat matMustache;

public:
    MustacheAnimation();
    virtual ~MustacheAnimation() override;

    void execute() override;
    void undo() override { }
};

