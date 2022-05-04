#pragma once

#include "LibUndoRedo/undoableaction.h"
#include "opencv2/opencv.hpp"

class FilterActions : public UndoableAction
{
protected:
    cv::Mat mat;

public:
    FilterActions();
    virtual ~FilterActions() override;

    void setMatrix(cv::Mat mat);
    cv::Mat getMatrix();
};
