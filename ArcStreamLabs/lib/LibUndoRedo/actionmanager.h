#pragma once

#include <stack>

#include "undoableaction.h"

class ActionManager
{
    private:
        std::stack<UndoableAction*> *undoStack;
        std::stack<UndoableAction*> *redoStack;

    public:
        ActionManager();
        ~ActionManager();

        void executeAction(UndoableAction* action);
        void undo();
        void redo();
};
