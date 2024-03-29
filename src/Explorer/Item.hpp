#pragma once

#include "ofxXmlSettings.h"
#include "../ScreenElements/Image.hpp"
#include "../ScreenElements/Video.hpp"
#include "../EdgeDistribution/EdgeHistogram.hpp"

class Item
{
public:
	Item(Image* image);
	Item(Video* video);
	~Item();

	void addTag(std::string tag);
	void removeTag(std::string tag);
	std::string getPropertyString() const;
	inline const std::vector<std::string>& getTags() { return tags; };
	void saveXML();

private:
	std::string name;
	int width, height;

	float lightness = 0;
	float brightness = 0;
	float hue = 0;

	float runtime = -1.;

	std::vector<std::string> tags;
	std::vector<float> edgeHistogramVals;
	std::vector<float> texHistogramVals;

};