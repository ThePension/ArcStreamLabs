#include "animationaction.h"

AnimationAction::AnimationAction() : UndoableAction() { }

AnimationAction::~AnimationAction() { }

void AnimationAction::setMatrix(cv::Mat mat)
{
    this->mat = mat;
}

cv::Mat AnimationAction::getMatrix()
{
    return this->mat;
}

