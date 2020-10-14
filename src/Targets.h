#pragma once
#include "RoundObject.h"

class Targets :
    public RoundObject
{
public:
    Targets(const float scale, const IRect& textureRect, FPoint& pos, Render::Texture* texture);
    ~Targets();
    void Draw() const;
private:
    Render::Texture* _texture;
};

