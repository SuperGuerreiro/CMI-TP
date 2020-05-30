#include "Item.hpp"

Item::Item(Image* image)
{
	name = image->getName();
	if (XML.loadFile(name + ".xml"))
	{
		printf("%s.xml loaded \n", name.c_str());

		//TODO: load the values
		std::string t = XML.getValue("Tags:aaa", "");

		lightness = XML.getValue("settings:lightness", 0.);
		brightness = XML.getValue("settings:brightness", 0.);
		hue = XML.getValue("settings:hue", 0.);
	}
	else
	{
		int width = image->getOFHandle().getWidth();
		int height = image->getOFHandle().getHeight();

		XML.setValue("settings:name", name);
		XML.setValue("settings:width", width);
		XML.setValue("settings:height", height);

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

		XML.setValue("settings:lightness", lightness);
		XML.setValue("settings:brightness", brightness);
		XML.setValue("settings:hue", hue);

		XML.setValue("Tags:rabo", "rabo");
		XML.setValue("Tags:aaa", "as");
		saveXML();
	}
}

Item::Item(Video* video)
{

}

Item::~Item()
{

}

void Item::saveXML()
{
	printf("%s.xml saved \n", name.c_str());
	XML.saveFile(name + ".xml");
}
