#include "Item.hpp"

Item::Item(Image* image)
{
	name = image->getName();
	if (XML.loadFile(name + ".xml"))
	{
		printf("%s_settings.xml loaded \n", name);

		//TODO: load the values
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
	printf("%s_settings.xml saved \n", name);
	XML.saveFile(name + ".xml");
}
