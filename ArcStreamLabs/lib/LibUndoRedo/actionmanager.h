#pragma once

#include <stack>
#include <vector>

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

        void addAction(UndoableAction* action);
        cv::Mat executeActions(cv::Mat);
        void removeFilters();
        void removeSpecialEffects();

        void undo();
        void redo();
};
