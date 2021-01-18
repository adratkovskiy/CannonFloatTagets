#pragma once
#include "RectObject.h"
class TargetsBlock :
    public RectObject
{
public:
    TargetsBlock(const float scale
        , const IRect& textureRect
        , const int health
    );
    ~TargetsBlock();

    int getHealth() const;

    void setHealth(const int health);

private:
    int _health;
};

