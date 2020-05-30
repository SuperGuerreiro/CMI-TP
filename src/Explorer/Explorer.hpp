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

	inline const Item& operator[](int i) const { return items[i]; };

private:
	std::vector<Item> items;

};