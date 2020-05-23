#include "TopBar.hpp"

TopBar::TopBar()
{
	xOffset = 0;
	yOffset = 0;
	width = 100;
	height = 30;
	padding = 10;
	hPadding = 5;
}

TopBar::TopBar(int xOffset, int yOffset, int width, int height, int padding, int hPadding)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), padding(padding), hPadding(hPadding)
{

}

TopBar::~TopBar()
{
	for each (ScreenElement* e in tabs)
	{
		delete e;
	}
}

void TopBar::update()
{
	for each (ScreenElement* tab in tabs)
	{
		tab->update();
	}
}

void TopBar::draw()
{
	ofSetColor(ofColor::cornflowerBlue);
	ofDrawRectangle(xOffset, yOffset, width, height);

	for each (ScreenElement* tab in tabs)
	{
		tab->draw();
	}
}

void TopBar::draw(int xOffset, int yOffset, int width, int height)
{
	this->draw(); //too lazy to do this
}

void TopBar::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->resetAttributes();
}

void TopBar::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->resetAttributes();
}

void TopBar::setFillMode(bool fill)
{

}

bool TopBar::onClick(int x, int y, int button)
{
	for each (ScreenElement* e in tabs)
	{
		if (e->onClick(x, y, button))
		{
			return true;
		}
	}
	return x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height;
}

void TopBar::addElement(ScreenElement * element, int width)
{
	tabs.push_back(element);
	tabLengths.push_back(width);
	this->resetAttributes();
}

void TopBar::resetAttributes()
{
	int x = padding;
	int h = height - padding * 2;
	int i = 0;
	for each (ScreenElement* tab in tabs)
	{
		tab->setOffset(x, padding);
		tab->setSize(tabLengths[i], h);
		x += tabLengths[i] + padding * 2 + hPadding;
		i++;
	}
}
