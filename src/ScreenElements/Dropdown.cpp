#include "Dropdown.hpp"

#define TEXT_PADDING 6

Dropdown::Dropdown()
{
	xOffset = 0;
	yOffset = 0;
	width = 100;
	height = 10;
	drawElements = false;
	name = "default_dropdown";
	color = ofColor::black;
}

Dropdown::Dropdown(int xOffset, int yOffset, int width, int height, std::string name, ofColor color, ofColor bgColor)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), name(name), color(color), bgColor(bgColor)
{
	drawElements = false;
}

Dropdown::~Dropdown()
{
	for each (ScreenElement* e in elements)
	{
		delete e;
	}
}

void Dropdown::update()
{
	for each (ScreenElement* e in elements)
	{
		e->update();
	}
}

void Dropdown::draw()
{
	ofSetColor(bgColor);
	ofDrawRectangle(xOffset, yOffset, width, height);
	ofSetColor(color);
	ofDrawBitmapString(name, xOffset, yOffset + CHAR_HEIGHT);
	if (drawElements)
	{
		ofSetColor(ofColor::white);
		ofDrawRectangle(xOffset, yOffset + height, maxElementWidth + TEXT_PADDING * 2, totalHeight);
		ofNoFill();
		ofSetColor(ofColor::black);
		ofDrawRectangle(xOffset, yOffset + height, maxElementWidth + TEXT_PADDING * 2, totalHeight);
		ofFill();
		int lineHeight = yOffset + height;
		for each (ScreenElement* e in elements)
		{
			e->draw();
			if (yOffset + height < lineHeight)
			{
				ofSetColor(ofColor::black);
				ofDrawLine(xOffset, lineHeight, xOffset + maxElementWidth + TEXT_PADDING * 2, lineHeight);
			}
			lineHeight += CHAR_HEIGHT + TEXT_PADDING * 2;
		}
	}
}

void Dropdown::draw(int xOffset, int yOffset, int width, int height)
{
	this->draw(); //xd
}

void Dropdown::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->resetAttributes();
}

void Dropdown::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->resetAttributes();
}

void Dropdown::setFillMode(bool fill)
{

}

bool Dropdown::onClick(int x, int y, int button)
{
	if (drawElements)
	{
		for each (ScreenElement* e in elements)
		{
			if (e->onClick(x, y, button))
			{
				drawElements = false;
				return true;
			}
		}
	}
	if (x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height)
	{
		drawElements = !drawElements;
		return true;
	}
	drawElements = false;
	return false;
}

void Dropdown::addElement(ScreenElement * element, int length)
{
	elements.push_back(element);
	if (maxElementWidth < length)
	{
		maxElementWidth = length;
		this->resetAttributes();
	}
}

void Dropdown::resetAttributes()
{
	int y = yOffset + height;
	for each (ScreenElement* e in elements)
	{
		e->setOffset(xOffset, y);
		e->setSize(maxElementWidth + TEXT_PADDING * 2, CHAR_HEIGHT + TEXT_PADDING * 2);
		y += CHAR_HEIGHT + TEXT_PADDING * 2;
	}
	totalHeight = y - yOffset - height;
}
