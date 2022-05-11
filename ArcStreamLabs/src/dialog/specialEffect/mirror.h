#pragma once

#include "specialeffectactions.h"

class Mirror : public SpecialEffectActions
{
public:
    Mirror();
    virtual ~Mirror() override;

    void execute() override;
    void undo() override { }
};
