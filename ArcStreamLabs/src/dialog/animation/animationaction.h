#pragma once

#include "LibUndoRedo/undoableaction.h"
#include "opencv2/opencv.hpp"

class AnimationAction : public UndoableAction
{
protected:
    cv::Mat mat;

public:
    AnimationAction();
    virtual ~AnimationAction() override;

    void setMatrix(cv::Mat mat);
    cv::Mat getMatrix();
};

