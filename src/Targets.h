#pragma once
#include "RoundObject.h"

class Targets :
    public RoundObject
{
public:
    Targets(const float scale
        , const IRect& textureRect
        , FPoint& pos
        , Render::Texture* texture
        , FPoint& moveVec
        , const float speed
        , const int topBorder
        , const int bottomBorder
        , const int leftBorder
        , const int rightBorder
    );
    void Draw() const;
    void Tick();
    void Collision(const FPoint& normal);
    void tooClose(const FPoint& victimCoord);

private:
    Render::Texture* _texture;
    FPoint _moveVec;
    float _speed;
    const int _topBorder;
    const int _bottomBorder;
    const int _leftBorder;
    const int _rightBorder;
};

