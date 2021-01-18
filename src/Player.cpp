#include "stdafx.h"
#include "Player.h"

Player::Player(const float scale
    , const IRect& textureRect
    , FPoint spawnPos
) :
    RectObject(scale, textureRect)
{
    setPosCenter(spawnPos);
}

Player::~Player()
{
}
