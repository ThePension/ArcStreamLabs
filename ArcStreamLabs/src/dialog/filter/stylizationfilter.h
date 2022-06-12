#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "filteractions.h"

class StylizationFilter : public FilterActions
{
public:
    StylizationFilter();
    virtual ~StylizationFilter() override;

    void execute() override;
    void undo() override { }
};

#endif // SOBELFILTER_H
