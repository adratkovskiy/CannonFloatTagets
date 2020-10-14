#include "stdafx.h"
#include "Targets.h"

Targets::Targets(const float scale, const IRect& textureRect, FPoint& pos, Render::Texture* texture) :
	RoundObject(scale, textureRect, pos),
	_texture(texture)
{
}

Targets::~Targets()
{
	bool boo;
}

void Targets::Draw() const
{
	_texture->Draw();
}
