#pragma once

#include "specialeffectactions.h"

class MosaicBlurEffect : public SpecialEffectActions
{
private:
    int tileSize;

public:
    MosaicBlurEffect();
    virtual ~MosaicBlurEffect() override;

    void execute() override;
    void undo() override { }

    void setTileSize(int);
};
