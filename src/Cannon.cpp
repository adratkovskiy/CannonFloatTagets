#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(float angle) : _angle(angle) {}

float& Cannon::getAngle()
{
    return _angle;
}

void Cannon::setAngle(float angle)
{
    _angle = angle;
}