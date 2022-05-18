#pragma once

#include "filteractions.h"

class LongExposure : public FilterActions
{
public:
    LongExposure();
    virtual ~LongExposure() override;

    void execute() override;
    void undo() override { }
};
