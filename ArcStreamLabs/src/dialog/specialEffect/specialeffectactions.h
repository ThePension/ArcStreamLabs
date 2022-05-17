#pragma once

#include "../../undo_redo/undoableaction.h"
#include "opencv2/opencv.hpp"

class SpecialEffectActions : public UndoableAction
{
protected:
    cv::Mat mat;

public:
    SpecialEffectActions();
    virtual ~SpecialEffectActions() override;

    void setMatrix(cv::Mat mat);
    cv::Mat getMatrix();
};
