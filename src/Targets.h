#pragma once
#include "RoundObject.h"

class Targets :
    public RoundObject
{
public:
    Targets(const float scale, const IRect& textureRect, FPoint& pos, Render::Texture* texture);
    void Draw() const;
    void Tick();

private:
    Render::Texture* _texture;
    FPoint moveTo;
};

