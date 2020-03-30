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
	selected = 0;
}

Collection::Collection(int xOffset, int yOffset, int width, int height)
{

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
}

void Collection::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Collection::setFillMode(bool fill)
{

}

void Collection::add(ScreenElement* e)
{
	elements.push_back(e);
}
