#include "DynamicDisplay.hpp"


DynamicDisplay::DynamicDisplay(int xOffset, int yOffset, int width, int height, Collection * collection, Camera * cam, Explorer * explorer)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), elements(collection), cam(cam), explorer(explorer)
{

}

void DynamicDisplay::update()
{
	cam->update();
	int v = cam->getNumFaces();
	if (v != viewers)
	{
		switch (v)
		{
		case 0:
			playlist = explorer->getPlaylist("zero_viewers");
			break;
		case 1:
			playlist = explorer->getPlaylist("one_viewers");
			break;
		case 2:
			playlist = explorer->getPlaylist("two_viewers");
			break;
		case 3:
			playlist = explorer->getPlaylist("three_viewers");
			break;
		default:
			break;
		}
		viewers = v;
	}
	if (playlist.empty())
	{
		elements->select(0);
	}
	else
	{
		elements->select(playlist[0]);
	}
	(*elements)[elements->getSelectedIndex()]->update();
}

void DynamicDisplay::draw()
{
	(*elements)[elements->getSelectedIndex()]->draw(xOffset, yOffset, width, height);
}

void DynamicDisplay::draw(int xOffset, int yOffset, int width, int height)
{
	(*elements)[elements->getSelectedIndex()]->draw(xOffset, yOffset, width, height);
}

void DynamicDisplay::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void DynamicDisplay::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void DynamicDisplay::setFillMode(bool fill)
{
	
}

bool DynamicDisplay::onClick(int x, int y, int button)
{
	return x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height;
}