#pragma once

#include <stack>

#include "undoableaction.h"
#include "opencv2/opencv.hpp"
#include "../../src/dialog/filter/filteractions.h"
#include "../../src/dialog/specialEffect/specialeffectactions.h"

class ActionManager
{
    private:
        std::stack<UndoableAction*> *undoStack;
        std::stack<UndoableAction*> *redoStack;

    public:
        ActionManager();
        ~ActionManager();

        void executeAction(UndoableAction* action);
        cv::Mat executeFilters(cv::Mat);
        cv::Mat executeSpecialEffects(cv::Mat);
        void undo();
        void redo();
};
