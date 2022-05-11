#pragma once

#include "specialeffectactions.h"

class MosaicBlurEffect : public SpecialEffectActions
{
public:
    MosaicBlurEffect();
    virtual ~MosaicBlurEffect() override;

    void execute() override;
    void undo() override { }
};
