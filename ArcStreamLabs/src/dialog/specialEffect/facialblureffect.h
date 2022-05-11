#pragma once

#include "specialeffectactions.h"

class FacialBlurEffect : public SpecialEffectActions
{
public:
    FacialBlurEffect();
    virtual ~FacialBlurEffect() override;

    void execute() override;
    void undo() override { }
};

