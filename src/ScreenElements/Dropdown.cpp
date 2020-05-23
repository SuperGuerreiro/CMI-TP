#include "Dropdown.hpp"

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

Dropdown::Dropdown(int xOffset, int yOffset, int width, int height, std::string name, ofColor color)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), name(name), color(color)
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
	ofSetColor(color);
	ofDrawBitmapString(name, xOffset, yOffset + CHAR_HEIGHT);
	if (drawElements)
	{
		ofSetColor(ofColor::white);
		ofDrawRectangle(xOffset, yOffset + height, maxElementWidth, totalHeight);
		for each (ScreenElement* e in elements)
		{
			e->draw();
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
		e->setSize(maxElementWidth, CHAR_HEIGHT);
		y += CHAR_HEIGHT;
	}
	totalHeight = y - yOffset - height;
}
