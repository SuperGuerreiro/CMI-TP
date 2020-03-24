#pragma once

#include "ofMain.h"

class ScreenElement
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual void setOffset(int xOffset, int yOffset) = 0;
	virtual void setSize(int width, int height) = 0;
	virtual void setFillMode(bool fill) = 0;
};