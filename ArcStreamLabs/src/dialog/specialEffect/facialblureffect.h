#pragma once

#include "specialeffectactions.h"

class FacialBlurEffect : public SpecialEffectActions
{
private:
    cv::CascadeClassifier cascade;

public:
    FacialBlurEffect();
    virtual ~FacialBlurEffect() override;

    void execute() override;
    void undo() override { }
};

