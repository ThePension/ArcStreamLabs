#pragma once

#include "filteractions.h"

class SobelFilter : public FilterActions
{
public:
    SobelFilter();
    virtual ~SobelFilter() override;

    void execute() override;
    void undo() override { }
};
