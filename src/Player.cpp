#include "stdafx.h"
#include "Player.h"

Player::Player(const float scale
    , const IRect& textureRect
    , FPoint pos
) :
    RectObject(scale, textureRect, pos)
{
}

Player::~Player()
{
}
