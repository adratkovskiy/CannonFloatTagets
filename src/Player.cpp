#include "stdafx.h"
#include "Player.h"

Player::Player(const float scale
    , const IRect& textureRect
    , FPoint pos
    , const int health
) :
    RectObject(scale, textureRect, pos, health)
{
}

Player::~Player()
{
}

void Player::setPrevPosX(const float x)
{
    _prevPosX = x;
}

const float Player::getPrevPosX() const
{
    return _prevPosX;
}
