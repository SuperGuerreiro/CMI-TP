#include "Group.hpp"

Group::Group()
{
	
}

Group::~Group()
{
	for each (ScreenElement* e in elements)
	{
		delete e;
	}
}

void Group::update()
{
	for each (ScreenElement* e in elements)
	{
		e->update();
	}
}

void Group::draw()
{
	for each (ScreenElement* e in elements)
	{
		e->draw();
	}
}

void Group::draw(int xOffset, int yOffset, int width, int height)
{
	this->draw(); //xd
}

void Group::setOffset(int xOffset, int yOffset)
{

}

void Group::setSize(int width, int height)
{

}

void Group::setFillMode(bool fill)
{

}

bool Group::onClick(int x, int y, int button)
{
	for each (ScreenElement* e in elements)
	{
		if (e->onClick(x, y, button))
		{
			return true;
		}
	}
	return false;
}
