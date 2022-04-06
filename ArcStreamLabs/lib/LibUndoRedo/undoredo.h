#pragma once

#include <iostream>
//#include <opencv2/opencv.hpp>

class UndoableAction
{
    public:
        UndoableAction();

        virtual void execute() = 0;
};
