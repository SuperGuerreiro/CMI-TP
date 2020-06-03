#include "Item.hpp"

Item::Item(Image* image)
{
	name = image->getName();
	ofxXmlSettings XML;

	if (XML.loadFile(name + ".xml"))
	{
		printf("%s.xml loaded \n", name.c_str());

		width = XML.getValue("settings:width", 0);
		height = XML.getValue("settings:height", 0);

		std::string t = XML.getValue("Tags:aaa", "");

		lightness = XML.getValue("settings:lightness", 0.);
		brightness = XML.getValue("settings:brightness", 0.);
		hue = XML.getValue("settings:hue", 0.);

		XML.getAttributeNames("Tags", tags);

		histogramVals.resize(16);
		histogramVals[0] = XML.getValue("histogram:0", -1.);
		histogramVals[1] = XML.getValue("histogram:1", -1.);
		histogramVals[2] = XML.getValue("histogram:2", -1.);
		histogramVals[3] = XML.getValue("histogram:3", -1.);
		histogramVals[4] = XML.getValue("histogram:4", -1.);
		histogramVals[5] = XML.getValue("histogram:5", -1.);
		histogramVals[6] = XML.getValue("histogram:6", -1.);
		histogramVals[7] = XML.getValue("histogram:7", -1.);
		histogramVals[8] = XML.getValue("histogram:8", -1.);
		histogramVals[9] = XML.getValue("histogram:9", -1.);
		histogramVals[10] = XML.getValue("histogram:10", -1.);
		histogramVals[11] = XML.getValue("histogram:11", -1.);
		histogramVals[12] = XML.getValue("histogram:12", -1.);
		histogramVals[13] = XML.getValue("histogram:13", -1.);
		histogramVals[14] = XML.getValue("histogram:14", -1.);
		histogramVals[15] = XML.getValue("histogram:15", -1.);
	}
	else
	{
		EdgeHistogram e = EdgeHistogram(image);

		width = image->getOFHandle().getWidth();
		height = image->getOFHandle().getHeight();

		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < height; k++)
			{
				ofColor currPixel = image->getOFHandle().getColor(j, k);

				lightness += currPixel.getLightness();
				brightness += currPixel.getBrightness();
				hue += currPixel.getHue();
			}
		}
		int imgSize = width * height;
		lightness = lightness / imgSize;
		brightness = brightness / imgSize;
		hue = hue / imgSize;

		histogramVals = e.getHistogramVals();

		saveXML();
	}
}

Item::Item(Video* video)
{
	ofxXmlSettings XML;
	name = video->getName();
	if (XML.loadFile(name + ".xml"))
	{
		printf("%s.xml loaded \n", name.c_str());

		width = XML.getValue("settings:width", 0);
		height = XML.getValue("settings:height", 0);

		std::string t = XML.getValue("Tags:aaa", "");

		lightness = XML.getValue("settings:lightness", 0.);
		brightness = XML.getValue("settings:brightness", 0.);
		hue = XML.getValue("settings:hue", 0.);

		runtime = XML.getValue("settings:runtime", -1.);

		XML.getAttributeNames("Tags", tags);
	}
	else
	{
		width = video->getOFHandle().getWidth();
		height = video->getOFHandle().getHeight();

		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < height; k++)
			{
				
				ofColor currPixel = video->getOFHandle().getPixels().getColor(j, k);

				lightness += currPixel.getLightness();
				brightness += currPixel.getBrightness();
				hue += currPixel.getHue();
			}
		}
		int vidSize = width * height;
		lightness = lightness / vidSize;
		brightness = brightness / vidSize;
		hue = hue / vidSize;

		runtime = video->getRuntime();

		saveXML();
	}
}

Item::~Item()
{

}

void Item::addTag(std::string tag)
{
	for each (std::string t in tags)
	{
		if (t == tag)
		{
			return;
		}
	}
	tags.push_back(tag);
	printf("Added %s to %s\n", tag.c_str(), name.c_str());
	saveXML();
}

void Item::removeTag(std::string tag)
{
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == tag)
		{
			printf("Removed %s from %s\n", tag.c_str(), name.c_str());
			tags.erase(tags.begin() + i);
			saveXML();
			return;
		}
	}
}

std::string Item::getPropertyString() const
{
	char edge[512];
	sprintf(edge, "Edge Histogram:\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n",
		histogramVals[0], histogramVals[1], histogramVals[2], histogramVals[3], 
		histogramVals[4], histogramVals[5], histogramVals[6], histogramVals[7], 
		histogramVals[8], histogramVals[9], histogramVals[10], histogramVals[11], 
		histogramVals[12], histogramVals[13], histogramVals[14], histogramVals[15]);
	char additional[512];
	if (runtime != -1.)
	{
		sprintf(additional, "Runtime: %fs\n", runtime);
	}
	else
	{
		sprintf(additional, "");
	}
	char res[1024];
	sprintf(res, "Filename: %s\nSize: %dx%d\n\nLightness: %f\nBrightness: %f\nHue: %f\n\n%s\n\n%s", name.c_str(), width, height, lightness, brightness, hue, edge, additional);
	return res;
}

void Item::saveXML()
{
	ofxXmlSettings XML;
	XML.setValue("settings:name", name);
	XML.setValue("settings:width", width);
	XML.setValue("settings:height", height);
	XML.setValue("settings:lightness", lightness);
	XML.setValue("settings:brightness", brightness);
	XML.setValue("settings:hue", hue);

	
	if (histogramVals.size() != 0) {
		char temp[20];
		for (int i = 0; i < histogramVals.size(); i++) {
			sprintf(temp, "edgeHistogram:%d", i);

			XML.setValue(temp, histogramVals[i]);
		}
	}

	XML.addTag("Tags");

	if (runtime != -1.)
	{
		XML.setValue("settings:runtime", runtime); //in seconds

	}

	printf("%s.xml saved \n", name.c_str());
	for each (std::string tag in tags)
	{
		XML.addAttribute("Tags", tag, 0, 0);
	}
	XML.saveFile(name + ".xml");
}
