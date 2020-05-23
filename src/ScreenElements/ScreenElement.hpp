#pragma once

#include "ofMain.h"

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 10

enum class ElementType
{
	None = 0,
	Image,
	Video,
	Triangle,
	Collection,
	TopBar,
	Dropdown,
	Button
};

using SimpleCallback = std::function<void()>;//void(*)();

class ScreenElement
{
public:

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void draw(int xOffset, int yOffset, int width, int height) = 0;

	virtual void setOffset(int xOffset, int yOffset) = 0;
	virtual void setSize(int width, int height) = 0;
	virtual void setFillMode(bool fill) = 0;

	virtual bool onClick(int x, int y, int button) = 0;

	virtual const ElementType getType() const = 0;
	virtual const std::string getName() const = 0;

};