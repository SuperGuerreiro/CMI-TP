#include "Item.hpp"

const char conv[16] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm', 'n', 'o', 'p', 'q' };

const int vidFrames = 50;

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
		histogramVals[0] = XML.getValue("edgeHistogram:a", -1.);
		histogramVals[1] = XML.getValue("edgeHistogram:b", -1.);
		histogramVals[2] = XML.getValue("edgeHistogram:c", -1.);
		histogramVals[3] = XML.getValue("edgeHistogram:d", -1.);
		histogramVals[4] = XML.getValue("edgeHistogram:e", -1.);
		histogramVals[5] = XML.getValue("edgeHistogram:f", -1.);
		histogramVals[6] = XML.getValue("edgeHistogram:g", -1.);
		histogramVals[7] = XML.getValue("edgeHistogram:h", -1.);
		histogramVals[8] = XML.getValue("edgeHistogram:i", -1.);
		histogramVals[9] = XML.getValue("edgeHistogram:j", -1.);
		histogramVals[10] = XML.getValue("edgeHistogram:k", -1.);
		histogramVals[11] = XML.getValue("edgeHistogram:m", -1.);
		histogramVals[12] = XML.getValue("edgeHistogram:n", -1.);
		histogramVals[13] = XML.getValue("edgeHistogram:o", -1.);
		histogramVals[14] = XML.getValue("edgeHistogram:p", -1.);
		histogramVals[15] = XML.getValue("edgeHistogram:k", -1.);
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

		char tag[64];
		sprintf(tag, "brightness_%c", conv[(int)brightness / 86]);
		addTag(tag);
		sprintf(tag, "hue_%c", conv[(int)hue / 86]);
		addTag(tag);

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

		histogramVals.resize(16);
		histogramVals[0] = XML.getValue("edgeHistogram:a", -1.);
		histogramVals[1] = XML.getValue("edgeHistogram:b", -1.);
		histogramVals[2] = XML.getValue("edgeHistogram:c", -1.);
		histogramVals[3] = XML.getValue("edgeHistogram:d", -1.);
		histogramVals[4] = XML.getValue("edgeHistogram:e", -1.);
		histogramVals[5] = XML.getValue("edgeHistogram:f", -1.);
		histogramVals[6] = XML.getValue("edgeHistogram:g", -1.);
		histogramVals[7] = XML.getValue("edgeHistogram:h", -1.);
		histogramVals[8] = XML.getValue("edgeHistogram:i", -1.);
		histogramVals[9] = XML.getValue("edgeHistogram:j", -1.);
		histogramVals[10] = XML.getValue("edgeHistogram:k", -1.);
		histogramVals[11] = XML.getValue("edgeHistogram:m", -1.);
		histogramVals[12] = XML.getValue("edgeHistogram:n", -1.);
		histogramVals[13] = XML.getValue("edgeHistogram:o", -1.);
		histogramVals[14] = XML.getValue("edgeHistogram:p", -1.);
		histogramVals[15] = XML.getValue("edgeHistogram:k", -1.);
	}
	else
	{
		ofVideoPlayer v = video->getOFHandle();
		width = v.getWidth();
		height = v.getHeight();

		histogramVals.resize(16);
		histogramVals[0] = 0;
		histogramVals[1] = 0;
		histogramVals[2] = 0;
		histogramVals[3] = 0;
		histogramVals[4] = 0;
		histogramVals[5] = 0;
		histogramVals[6] = 0;
		histogramVals[7] = 0;
		histogramVals[8] = 0;
		histogramVals[9] = 0;
		histogramVals[10] = 0;
		histogramVals[11] = 0;
		histogramVals[12] = 0;
		histogramVals[13] = 0;
		histogramVals[14] = 0;
		histogramVals[15] = 0;
		for (int i = 0; i < vidFrames; i++)
		{
			v.setPaused(false);
			v.setFrame((v.getTotalNumFrames() / vidFrames) * i);
			v.setPaused(true);
			v.update();
			while (!v.isFrameNew())
			{
				v.update();
			}

			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < height; k++)
				{
				
					ofColor currPixel = v.getPixels().getColor(j, k);

					lightness += currPixel.getLightness();
					brightness += currPixel.getBrightness();
					hue += currPixel.getHue();
				}
			}

			EdgeHistogram e(v.getPixels());
			std::vector<float> frameEdges = e.getHistogramVals();
			histogramVals[0] += frameEdges[0];
			histogramVals[1] += frameEdges[1];
			histogramVals[2] += frameEdges[2];
			histogramVals[3] += frameEdges[3];
			histogramVals[4] += frameEdges[4];
			histogramVals[5] += frameEdges[5];
			histogramVals[6] += frameEdges[6];
			histogramVals[7] += frameEdges[7];
			histogramVals[8] += frameEdges[8];
			histogramVals[9] += frameEdges[9];
			histogramVals[10] += frameEdges[10];
			histogramVals[11] += frameEdges[11];
			histogramVals[12] += frameEdges[12];
			histogramVals[13] += frameEdges[13];
			histogramVals[14] += frameEdges[14];
			histogramVals[15] += frameEdges[15];
		}
		size_t vidSize = width * height * vidFrames;
		lightness = lightness / vidSize;
		brightness = brightness / vidSize;
		hue = hue / vidSize;

		histogramVals[0] = histogramVals[0] / 16;
		histogramVals[1] = histogramVals[1] / 16;
		histogramVals[2] = histogramVals[2] / 16;
		histogramVals[3] = histogramVals[3] / 16;
		histogramVals[4] = histogramVals[4] / 16;
		histogramVals[5] = histogramVals[5] / 16;
		histogramVals[6] = histogramVals[6] / 16;
		histogramVals[7] = histogramVals[7] / 16;
		histogramVals[8] = histogramVals[8] / 16;
		histogramVals[9] = histogramVals[9] / 16;
		histogramVals[10] = histogramVals[10] / 16;
		histogramVals[11] = histogramVals[11] / 16;
		histogramVals[12] = histogramVals[12] / 16;
		histogramVals[13] = histogramVals[13] / 16;
		histogramVals[14] = histogramVals[14] / 16;
		histogramVals[15] = histogramVals[15] / 16;

		runtime = video->getRuntime();

		char tag[64];
		sprintf(tag, "brightness_%c", conv[(int)brightness / 86]);
		addTag(tag);
		sprintf(tag, "hue_%c", conv[(int)hue / 86]);
		addTag(tag);

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
			sprintf(temp, "edgeHistogram:%c", conv[i]);

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

