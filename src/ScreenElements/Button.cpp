#include "Button.hpp"

Button::Button()
{

}

Button::Button(int xOffset, int yOffset, int width, int height, std::string name, ofColor color, ofColor bgColor, SimpleCallback callback)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), name(name), color(color), bgColor(bgColor), callback(callback)
{

}

Button::~Button()
{

}

void Button::update()
{

}

void Button::draw()
{
	ofSetColor(bgColor);
	ofDrawRectangle(xOffset, yOffset, width, height);
	ofSetColor(color);
	ofDrawBitmapString(name, xOffset + (width - name.length() * CHAR_WIDTH) / 2, yOffset + CHAR_HEIGHT + (height - CHAR_HEIGHT) / 2);
}

void Button::draw(int xOffset, int yOffset, int width, int height)
{
	ofSetColor(bgColor);
	ofDrawRectangle(xOffset, yOffset, width, height);
	ofSetColor(color);
	ofDrawBitmapString(name, xOffset + (width - name.length() * CHAR_WIDTH) / 2, yOffset + CHAR_HEIGHT + (height - CHAR_HEIGHT) / 2);
}

void Button::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Button::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Button::setFillMode(bool fill)
{

}

bool Button::onClick(int x, int y, int button)
{
	if (x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height)
	{
		callback();
		return true;
	}
	return false;
}
