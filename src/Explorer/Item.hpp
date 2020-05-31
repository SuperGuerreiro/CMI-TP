#pragma once

#include "ofxXmlSettings.h"
#include "../ScreenElements/Image.hpp"
#include "../ScreenElements/Video.hpp"

class Item
{
public:
	Item(Image* image);
	Item(Video* video);
	~Item();

	std::string getPropertyString() const;
	void saveXML();

private:
	std::string name;
	int width, height;

	float lightness = 0;
	float brightness = 0;
	float hue = 0;

	ofxXmlSettings XML;

};