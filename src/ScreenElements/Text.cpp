#include "Text.hpp"

Text::Text()
{
	xOffset = 0;
	yOffset = 0;
	text = "";
	color = ofColor::black;
}

Text::Text(std::string text, ofColor color, int xOffset, int yOffset) : text(text), color(color), xOffset(xOffset), yOffset(yOffset)
{

}

Text::~Text()
{

}

void Text::update()
{

}

void Text::draw()
{
	ofSetColor(color);
	ofDrawBitmapString(text, xOffset, yOffset + CHAR_HEIGHT);
}

void Text::draw(int xOffset, int yOffset, int width, int height)
{
	ofSetColor(color);
	ofDrawBitmapString(text, xOffset, yOffset + CHAR_HEIGHT);
}

void Text::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Text::setSize(int width, int height)
{

}

void Text::setFillMode(bool fill)
{

}

bool Text::onClick(int x, int y, int button)
{
	return false;
}
