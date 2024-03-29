#pragma once

#include "ofMain.h"
#include "Item.hpp"
#include "../ScreenElements/Image.hpp"
#include "../ScreenElements/Video.hpp"

class Explorer
{
public:
	Explorer();
	~Explorer();

	void add(Image* imageHandle);
	void add(Video* videoHandle);

	void generatePlaylists();

	inline Item* operator[](int i) { return &items[i]; };
	inline std::vector<int>& getPlaylist(std::string tag) { return playlists[tag]; };

private:
	std::vector<Item> items;

	std::map<std::string, std::vector<int>> playlists;
};