#pragma once

#include "specialeffectactions.h"
#include "../../helper.h"

class FacialBlurEffect : public SpecialEffectActions
{
private:
    cv::CascadeClassifier cascadeFrontalFace;
    cv::CascadeClassifier cascadeProfileFace;

public:
    FacialBlurEffect();
    virtual ~FacialBlurEffect() override;

    void execute() override;
    void undo() override { }
};

