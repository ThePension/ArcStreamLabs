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

void ActionManager::addAction(UndoableAction* action)
{
    action->execute();
    this->undoStack->push(action);
}

cv::Mat ActionManager::executeActions(cv::Mat mat)
{
    std::stack<UndoableAction*> *tempStack = new std::stack<UndoableAction*>();

    while(!this->undoStack->empty())
    {
        UndoableAction * ua = this->undoStack->top();
        this->undoStack->pop();

        FilterActions * fa = dynamic_cast<FilterActions *>(ua);
        SpecialEffectActions * sea = dynamic_cast<SpecialEffectActions *>(ua);

        if(fa != nullptr)
        {
            fa->setMatrix(mat);
            fa->execute();
            mat = fa->getMatrix();
        }
        else if (sea != nullptr)
        {
            sea->setMatrix(mat);
            sea->execute();
            mat = sea->getMatrix();
        }

        tempStack->push(ua);
    }

    while(!tempStack->empty())
    {
        this->undoStack->push(tempStack->top());
        tempStack->pop();
    }

    delete tempStack; tempStack = nullptr;
    return mat;
}

void ActionManager::removeFilters()
{
    std::stack<UndoableAction*> *tempStack = new std::stack<UndoableAction*>();

    while(!this->undoStack->empty())
    {
        UndoableAction * ua = this->undoStack->top();
        this->undoStack->pop();

        FilterActions * fa = dynamic_cast<FilterActions *>(ua);

        if(fa == nullptr)
        {
            tempStack->push(ua);
        }
        else
        {
            this->redoStack->push(ua);
        }
    }

    while(!tempStack->empty())
    {
        this->undoStack->push(tempStack->top());
        tempStack->pop();
    }

    delete tempStack; tempStack = nullptr;
}

void ActionManager::removeSpecialEffects()
{
    std::stack<UndoableAction*> *tempStack = new std::stack<UndoableAction*>();

    while(!this->undoStack->empty())
    {
        UndoableAction * ua = this->undoStack->top();
        this->undoStack->pop();

        SpecialEffectActions * sea = dynamic_cast<SpecialEffectActions *>(ua);

        if(sea == nullptr)
        {
            tempStack->push(ua);
        }
        else
        {
            this->redoStack->push(ua);
        }
    }

    while(!tempStack->empty())
    {
        this->undoStack->push(tempStack->top());
        tempStack->pop();
    }

    delete tempStack; tempStack = nullptr;
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
