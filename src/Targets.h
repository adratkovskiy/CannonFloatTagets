#pragma once
#include "RoundObject.h"

class Targets :
    public RoundObject
{
public:
    Targets(const float scale, const IRect& textureRect, FPoint& pos, Render::Texture* texture, float moveAngle);
    void Draw() const;
    void Tick();

private:
    Render::Texture* _texture;
    float _moveAngle;
    float _speed = 1.f;
};

