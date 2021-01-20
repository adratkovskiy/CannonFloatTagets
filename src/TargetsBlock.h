#pragma once
#include "RectObject.h"
class TargetsBlock :
    public RectObject
{
public:
    TargetsBlock(const float scale
        , const IRect& textureRect
        , const FPoint& pos
        , const int health
        , const float speed
        , bool* toLeft
        , const int leftBorder
        , const int rightBorder
    );
    ~TargetsBlock();

    int getHealth() const;
    bool* getToLeft();

    void setHealth(const int health);
    void click(const IPoint& mouse_pos);
    void move();
    //void hit(FPoint& cannonball, float radius);
    void hit();

private:
    int _health;
    float _speed;
    bool* _toLeft;
    int _leftBorder;
    int _rightBorder;
};

