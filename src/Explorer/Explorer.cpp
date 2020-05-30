#include "Explorer.hpp"

Explorer::Explorer()
{

}

Explorer::~Explorer()
{

}

void Explorer::add(Image* imageHandle)
{
	imageHandle->setId(items.size());
	items.push_back(Item(imageHandle));
}

void Explorer::add(Video* videoHandle)
{
	videoHandle->setId(items.size());
	items.push_back(Item(videoHandle));
}
