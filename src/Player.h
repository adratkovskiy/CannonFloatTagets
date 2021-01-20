#pragma once
#include "RectObject.h"
class Player :
    public RectObject
{
public:
    Player(const float scale
        , const IRect& textureRect
        , FPoint pos
        , const int health
    );
    ~Player();

    void setPrevPosX(const float x);

    const float getPrevPosX() const;

private:
    float _prevPosX;
};
