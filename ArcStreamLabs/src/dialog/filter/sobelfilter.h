#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "filteractions.h"

class SobelFilter : public FilterActions
{
public:
    SobelFilter();

    virtual ~SobelFilter() override;

    void execute() override;
    void undo() override { }
};

#endif // SOBELFILTER_H
