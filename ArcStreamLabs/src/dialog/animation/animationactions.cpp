#include "animationactions.h"

AnimationActions::AnimationActions() : UndoableAction() { }

AnimationActions::~AnimationActions() { }

void AnimationActions::setMatrix(cv::Mat mat)
{
    this->mat = mat;
}

cv::Mat AnimationActions::getMatrix()
{
    return this->mat;
}

