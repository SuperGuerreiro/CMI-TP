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

void Explorer::generatePlaylists()
{
	playlists.clear();
	for (int i = 0; i < items.size(); i++)
	{
		std::vector<std::string> tags = items[i].getTags();
		for each (std::string tag in tags)
		{
			playlists[tag].push_back(i);
		}

		//TODO: maybe add playlists for brightness and stuff
	}
}
