#include "filteractions.h"

FilterActions::FilterActions() : UndoableAction()
{

}

FilterActions::~FilterActions()
{

}

void FilterActions::setMatrix(cv::Mat mat)
{
    this->mat = mat;
}

cv::Mat FilterActions::getMatrix()
{
    return this->mat;
}
