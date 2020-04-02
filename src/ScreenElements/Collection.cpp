#include "Collection.hpp"


Collection::Collection()
{
	xOffset = 0;
	yOffset = 0;
	width = 400;
	height = 400;
	elementWidth = 80;
	elementHeight = 80;
	padding = 10;
	selected = -1;
	scrollVal = 0.0f;
	resetAttributes();
}

Collection::Collection(int xOffset, int yOffset, int width, int height, int elementWidth, int elementHeight, int padding)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), elementWidth(elementWidth), elementHeight(elementHeight), padding(padding)
{
	scrollVal = 0.0f;
	resetAttributes();
}

Collection::~Collection()
{
	for each (ScreenElement* e in elements)
	{
		free(e);
	}
}

void Collection::update()
{
	for each (ScreenElement* e in elements)
	{
		e->update();
	}
}

void Collection::draw()
{
	for each (ScreenElement* e in elements)
	{
		e->draw();
	}
}

void Collection::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	resetAttributes();
}

void Collection::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
	resetAttributes();
}

void Collection::setFillMode(bool fill)
{

}

void Collection::add(ScreenElement* e)
{
	int eleXOffset = xOffset + padding + spacing / 2 + ((int)elements.size() % perRow) * (padding + elementWidth + spacing);
	int eleYOffset = yOffset + padding + ((int)elements.size() / perRow) * (padding + elementHeight) - scrollOffset * scrollVal;
	e->setOffset(eleXOffset, eleYOffset);
	e->setSize(elementWidth, elementHeight);
	elements.push_back(e);
}

void Collection::setElementsSize(int width, int height)
{
	this->elementWidth = width;
	this->elementHeight = height;
	resetAttributes();
}

void Collection::scroll(float value)
{
	scrollVal -= scrollMult * value;
	scrollVal = std::min(scrollVal, 1.0f);
	scrollVal = std::max(scrollVal, 0.0f);
	resetAttributes();
}

void Collection::resetAttributes()
{
	int i = 0;
	int eleXOffset, eleYOffset;
	perRow = std::max((width - padding) / (elementWidth + padding), 1);
	int rows = std::ceilf((float)elements.size() / perRow);
	scrollMult = ((float)(padding + elementHeight) * 0.002) / rows; //TODO: change
	scrollOffset = padding + (padding + elementHeight) * rows - height;
	scrollOffset = std::max(scrollOffset, 0);
	spacing = (width - (padding + perRow * (padding + elementWidth))) / perRow;
	for each (ScreenElement* e in elements)
	{
		eleXOffset = xOffset + padding + spacing / 2 + (i % perRow) * (padding + elementWidth + spacing);
		eleYOffset = yOffset + padding + (i / perRow) * (padding + elementHeight) - scrollOffset * scrollVal;
		e->setOffset(eleXOffset, eleYOffset);
		e->setSize(elementWidth, elementHeight);
		i++;
	}
}
