#pragma once

#include "ofMain.h";
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

private:
	std::vector<Item> items;

};