#include "Collection.hpp"

#define SELECTED_QUAD_PADDING 4

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
	if (selected != -1)
	{
		int quadXOffset, quadYOffset;
		quadXOffset = xOffset + padding + spacing / 2 + (selected % perRow) * (padding + elementWidth + spacing) - SELECTED_QUAD_PADDING;
		quadYOffset = yOffset + padding + (selected / perRow) * (padding + elementHeight) - scrollOffset * scrollVal - SELECTED_QUAD_PADDING;
		ofSetColor(ofColor::blue);
		ofDrawRectangle(quadXOffset, quadYOffset, elementWidth + SELECTED_QUAD_PADDING * 2, elementHeight + SELECTED_QUAD_PADDING * 2);
	}
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

bool Collection::onClick(int x, int y, int button)
{
	if (x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height)
	{
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i]->onClick(x, y, button))
			{
				selected = i;
				break;
			}
		}
		return true;
	}
	return false;
}

void Collection::add(ScreenElement* e)
{
	int eleXOffset = xOffset + padding + spacing / 2 + ((int)elements.size() % perRow) * (padding + elementWidth + spacing);
	int eleYOffset = yOffset + padding + ((int)elements.size() / perRow) * (padding + elementHeight) - scrollOffset * scrollVal;
	e->setOffset(eleXOffset, eleYOffset);
	e->setSize(elementWidth, elementHeight);
	elements.push_back(e);
}

std::string Collection::getSelected()
{
	if (selected == -1)
	{
		return "";
	}
	return elements[selected]->getName();
}

void Collection::unselect()
{
	selected = -1;
}

void Collection::onKeyPressed(int key)
{
	switch (key)
	{
	case OF_KEY_UP:
		selected = selected - perRow < 0 ? elements.size() - 1 : selected - perRow;
		break;
	case OF_KEY_DOWN:
		selected = selected + perRow < elements.size() ? selected + perRow : 0;
		break;
	case OF_KEY_LEFT:
		selected = selected - 1 < 0 ? elements.size() - 1 : selected - 1;
		break;
	case OF_KEY_RIGHT:
		selected = selected + 1 < elements.size() ? selected + 1 : 0;
		break;
	default:
		break;
	}
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
