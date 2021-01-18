#pragma once
#include "RectObject.h"
class Player :
    public RectObject
{
public:
    Player(const float scale
        , const IRect& textureRect
        , FPoint pos
    );
    ~Player();
};
