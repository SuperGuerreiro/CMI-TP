#pragma once

#include "ofMain.h"

enum class ElementType
{
	None = 0,
	Image,
	Video,
	Triangle,
	Collection
};

class ScreenElement
{
public:

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual void setOffset(int xOffset, int yOffset) = 0;
	virtual void setSize(int width, int height) = 0;
	virtual void setFillMode(bool fill) = 0;

	virtual ElementType getType() = 0;

};