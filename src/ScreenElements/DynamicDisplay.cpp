#include "DynamicDisplay.hpp"


DynamicDisplay::DynamicDisplay(int xOffset, int yOffset, int width, int height, Collection * collection, Camera * cam, Explorer * explorer)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height), elements(collection), cam(cam), explorer(explorer)
{

}

void DynamicDisplay::update()
{
	cam->update();
	count += 1 / ofGetFrameRate();
	if (maxCount < count)
	{
		count = 0;
	}
	if (count == 0)
	{
		int v = cam->getNumFaces();
		if (v != viewers)
		{
			switch (v)
			{
			case 0:
				vPlaylist = explorer->getPlaylist("zero_viewers");
				break;
			case 1:
				vPlaylist = explorer->getPlaylist("one_viewers");
				break;
			case 2:
				vPlaylist = explorer->getPlaylist("two_viewers");
				break;
			case 3:
				vPlaylist = explorer->getPlaylist("three_viewers");
				break;
			default:
				break;
			}
			viewers = v;
		}
		cam->getProps(&brightness, &hue); // 256 total values
		int bType = brightness / 86;
		switch (bType)
		{
		case 0:
			bPlaylist = explorer->getPlaylist("brightness_a");
			break;
		case 1:
			bPlaylist = explorer->getPlaylist("brightness_b");
			break;
		case 2:
			bPlaylist = explorer->getPlaylist("brightness_c");
			break;
		default:
			break;
		}
		int hType = hue / 86;
		switch (hType)
		{
		case 0:
			hPlaylist = explorer->getPlaylist("hue_a");
			break;
		case 1:
			hPlaylist = explorer->getPlaylist("hue_b");
			break;
		case 2:
			hPlaylist = explorer->getPlaylist("hue_c");
			break;
		default:
			break;
		}
		if (vPlaylist.empty() && bPlaylist.empty() && hPlaylist.empty())
		{
			idx++;
			elements->select(idx % elements->getSize());
		}
		else
		{
			std::vector<int>* t;
			do
			{
				idx++;
				int pid = idx % 3;
				switch (pid)
				{
				case 0:
					t = &vPlaylist;
					break;
				case 1:
					t = &bPlaylist;
					break;
				case 2:
					t = &hPlaylist;
					break;
				default:
					break;
				}
			} while (t->empty());
			elements->select((*t)[idx % t->size()]);
		}
		if ((*elements)[elements->getSelectedIndex()]->getType() == ElementType::Video)
		{
			maxCount = ((Video*)(*elements)[elements->getSelectedIndex()])->getRuntime();
		}
		else
		{
			maxCount = 5;
		}
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
