#include "undoableactiontest.h"

UndoableActionTest::UndoableActionTest(int newValue, int * value)
{
    this->backup = *value;
    this->newValue = newValue;
    this->value = value;
}

UndoableActionTest::~UndoableActionTest()
{
    delete this->value; this->value = nullptr;
}

void UndoableActionTest::execute()
{
    *this->value = this->newValue;
}

void UndoableActionTest::undo()
{
    *this->value = this->backup;
}


