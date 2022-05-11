#pragma once

#include "animationactions.h"

class MustacheAnimation : public AnimationActions
{
public:
    MustacheAnimation();
    virtual ~MustacheAnimation() override;

    void execute() override;
    void undo() override { }
};

