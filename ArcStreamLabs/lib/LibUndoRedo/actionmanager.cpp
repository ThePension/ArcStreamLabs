#include "actionmanager.h"

ActionManager::ActionManager()
{
    this->undoStack = new std::stack<UndoableAction*>();
    this->redoStack = new std::stack<UndoableAction*>();
}

ActionManager::~ActionManager()
{
    while(!this->undoStack->empty())
    {
        UndoableAction *action = this->undoStack->top();
        this->undoStack->pop();
        delete action;
    }

    while(!this->redoStack->empty())
    {
        UndoableAction *action = this->redoStack->top();
        this->redoStack->pop();
        delete action;
    }
}

void ActionManager::executeAction(UndoableAction* action)
{
    action->execute();

    this->undoStack->push(action);
}

void ActionManager::undo()
{
    if(!this->undoStack->empty())
    {
        UndoableAction* action = this->undoStack->top();
        this->undoStack->pop();
        action->undo();
        this->redoStack->push(action);
    }
}

void ActionManager::redo()
{
    if(!this->redoStack->empty())
    {
        UndoableAction* action = this->redoStack->top();
        this->redoStack->pop();
        action->execute();
        this->undoStack->push(action);
    }
}
