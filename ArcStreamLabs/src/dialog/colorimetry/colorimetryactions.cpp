#include "colorimetryactions.h"
#include <QSlider>


ColorimetryActions::ColorimetryActions(int **values, QSlider *** slidersTab)
{
    this->slidersTab = slidersTab;
    this->values = values;

    this->backup = new int*[3];

    for (int i = 0; i < 3; i++)
    {
        this->backup[i] = new int[3];
    }
}

ColorimetryActions::~ColorimetryActions()
{
    for(int i=0; i<3; i++)
    {
        delete [] this->backup[i];
        delete [] this->values[i];
    }

    delete [] this->backup;
    delete [] this->values;
}

void ColorimetryActions::execute()
{
    this->backup[0][0] = this->slidersTab[0][0]->value();
    this->backup[0][1] = this->slidersTab[0][1]->value();
    this->backup[0][2] = this->slidersTab[0][2]->value();
    this->backup[1][0] = this->slidersTab[1][0]->value();
    this->backup[1][1] = this->slidersTab[1][1]->value();
    this->backup[1][2] = this->slidersTab[1][2]->value();
    this->backup[2][0] = this->slidersTab[2][0]->value();
    this->backup[2][1] = this->slidersTab[2][1]->value();
    this->backup[2][2] = this->slidersTab[2][2]->value();

    this->slidersTab[0][0]->setValue(this->values[0][0]);
    this->slidersTab[0][1]->setValue(this->values[0][1]);
    this->slidersTab[0][2]->setValue(this->values[0][2]);
    this->slidersTab[1][0]->setValue(this->values[1][0]);
    this->slidersTab[1][1]->setValue(this->values[1][1]);
    this->slidersTab[1][2]->setValue(this->values[1][2]);
    this->slidersTab[2][0]->setValue(this->values[2][0]);
    this->slidersTab[2][1]->setValue(this->values[2][1]);
    this->slidersTab[2][2]->setValue(this->values[2][2]);
}

void ColorimetryActions::undo()
{
    this->slidersTab[0][0]->setValue(this->backup[0][0]);
    this->slidersTab[0][1]->setValue(this->backup[0][1]);
    this->slidersTab[0][2]->setValue(this->backup[0][2]);
    this->slidersTab[1][0]->setValue(this->backup[1][0]);
    this->slidersTab[1][1]->setValue(this->backup[1][1]);
    this->slidersTab[1][2]->setValue(this->backup[1][2]);
    this->slidersTab[2][0]->setValue(this->backup[2][0]);
    this->slidersTab[2][1]->setValue(this->backup[2][1]);
    this->slidersTab[2][2]->setValue(this->backup[2][2]);
}
