#pragma once
#include "RoundObject.h"
#include "Functions.h"

class Targets :
    public RoundObject
{
public:
    Targets(const float scale
        , const IRect& textureRect
        , const FPoint& pos
        , Render::Texture* texture
        , const FPoint& moveVec
        , const float speed
        , const int topBorder
        , const int bottomBorder
        , const int leftBorder
        , const int rightBorder
        , const int points
    );
    ~Targets();
    void Draw() const;
    void Tick();
    void Collision(const FPoint& normal);
    void tooClose(Targets& victim);
    
    const int getPoints() const noexcept;

private:
    Render::Texture* _texture;
    FPoint _moveVec;
    float _speed;
    const int _topBorder;
    const int _bottomBorder;
    const int _leftBorder;
    const int _rightBorder;
    const int _points;
};

