
#include "specialeffectactions.h"

SpecialEffectActions::SpecialEffectActions() : UndoableAction()
{

}

SpecialEffectActions::~SpecialEffectActions()
{

}

void SpecialEffectActions::setMatrix(cv::Mat mat)
{
    this->mat = mat;
}

cv::Mat SpecialEffectActions::getMatrix()
{
    return this->mat;
}
