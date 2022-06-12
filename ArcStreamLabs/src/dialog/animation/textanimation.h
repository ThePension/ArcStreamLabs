#pragma once

#include "animationactions.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class TextAnimation : public AnimationActions
{
private:
    QString text;

    float x, y, w, h;
    float xspeed, yspeed;

    cv::Point getNewPosition();
    void moveCheck();

public:
    TextAnimation(QString text);
    virtual ~TextAnimation() override;

    void execute() override;
    void undo() override { }
};
