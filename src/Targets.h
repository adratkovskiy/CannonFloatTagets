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
    Targets& operator=(const Targets& obj);
    ~Targets();

    void Draw() const;
    void Tick();
    void Collision(const FPoint& normal);
    void tooClose(Targets& victim);
    
    int getPoints() const;

private:
    Render::Texture* _texture;
    FPoint _moveVec;
    float _speed;
    int _topBorder;
    int _bottomBorder;
    int _leftBorder;
    int _rightBorder;
    int _points;
};

