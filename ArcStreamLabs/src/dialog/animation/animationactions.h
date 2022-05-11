#pragma once

#include "LibUndoRedo/undoableaction.h"
#include "opencv2/opencv.hpp"

class AnimationActions : public UndoableAction
{
protected:
    cv::Mat mat;

public:
    AnimationActions();
    virtual ~AnimationActions() override;

    void setMatrix(cv::Mat mat);
    cv::Mat getMatrix();
};

