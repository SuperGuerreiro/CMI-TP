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

		lightness = XML.getValue("settings:lightness", 0.);
		brightness = XML.getValue("settings:brightness", 0.);
		hue = XML.getValue("settings:hue", 0.);

		XML.getAttributeNames("Tags", tags);

		edgeHistogramVals.resize(16);
		edgeHistogramVals[0] = XML.getValue("edgeHistogram:a", -1.);
		edgeHistogramVals[1] = XML.getValue("edgeHistogram:b", -1.);
		edgeHistogramVals[2] = XML.getValue("edgeHistogram:c", -1.);
		edgeHistogramVals[3] = XML.getValue("edgeHistogram:d", -1.);
		edgeHistogramVals[4] = XML.getValue("edgeHistogram:e", -1.);
		edgeHistogramVals[5] = XML.getValue("edgeHistogram:f", -1.);
		edgeHistogramVals[6] = XML.getValue("edgeHistogram:g", -1.);
		edgeHistogramVals[7] = XML.getValue("edgeHistogram:h", -1.);
		edgeHistogramVals[8] = XML.getValue("edgeHistogram:i", -1.);
		edgeHistogramVals[9] = XML.getValue("edgeHistogram:j", -1.);
		edgeHistogramVals[10] = XML.getValue("edgeHistogram:k", -1.);
		edgeHistogramVals[11] = XML.getValue("edgeHistogram:m", -1.);
		edgeHistogramVals[12] = XML.getValue("edgeHistogram:n", -1.);
		edgeHistogramVals[13] = XML.getValue("edgeHistogram:o", -1.);
		edgeHistogramVals[14] = XML.getValue("edgeHistogram:p", -1.);
		edgeHistogramVals[15] = XML.getValue("edgeHistogram:q", -1.);

		texHistogramVals.resize(16);
		texHistogramVals[0] = XML.getValue("texHistogram:a", -1.);
		texHistogramVals[1] = XML.getValue("texHistogram:b", -1.);
		texHistogramVals[2] = XML.getValue("texHistogram:c", -1.);
		texHistogramVals[3] = XML.getValue("texHistogram:d", -1.);
		texHistogramVals[4] = XML.getValue("texHistogram:e", -1.);
		texHistogramVals[5] = XML.getValue("texHistogram:f", -1.);
		texHistogramVals[6] = XML.getValue("texHistogram:g", -1.);
		texHistogramVals[7] = XML.getValue("texHistogram:h", -1.);
		texHistogramVals[8] = XML.getValue("texHistogram:i", -1.);
		texHistogramVals[9] = XML.getValue("texHistogram:j", -1.);
		texHistogramVals[10] = XML.getValue("texHistogram:k", -1.);
		texHistogramVals[11] = XML.getValue("texHistogram:m", -1.);
		texHistogramVals[12] = XML.getValue("texHistogram:n", -1.);
		texHistogramVals[13] = XML.getValue("texHistogram:o", -1.);
		texHistogramVals[14] = XML.getValue("texHistogram:p", -1.);
		texHistogramVals[15] = XML.getValue("texHistogram:q", -1.);
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

		edgeHistogramVals = e.getHistogramVals();
		texHistogramVals = e.getTextureHistogramVals();

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

		lightness = XML.getValue("settings:lightness", 0.);
		brightness = XML.getValue("settings:brightness", 0.);
		hue = XML.getValue("settings:hue", 0.);

		runtime = XML.getValue("settings:runtime", -1.);

		XML.getAttributeNames("Tags", tags);

		edgeHistogramVals.resize(16);
		edgeHistogramVals[0] = XML.getValue("edgeHistogram:a", -1.);
		edgeHistogramVals[1] = XML.getValue("edgeHistogram:b", -1.);
		edgeHistogramVals[2] = XML.getValue("edgeHistogram:c", -1.);
		edgeHistogramVals[3] = XML.getValue("edgeHistogram:d", -1.);
		edgeHistogramVals[4] = XML.getValue("edgeHistogram:e", -1.);
		edgeHistogramVals[5] = XML.getValue("edgeHistogram:f", -1.);
		edgeHistogramVals[6] = XML.getValue("edgeHistogram:g", -1.);
		edgeHistogramVals[7] = XML.getValue("edgeHistogram:h", -1.);
		edgeHistogramVals[8] = XML.getValue("edgeHistogram:i", -1.);
		edgeHistogramVals[9] = XML.getValue("edgeHistogram:j", -1.);
		edgeHistogramVals[10] = XML.getValue("edgeHistogram:k", -1.);
		edgeHistogramVals[11] = XML.getValue("edgeHistogram:m", -1.);
		edgeHistogramVals[12] = XML.getValue("edgeHistogram:n", -1.);
		edgeHistogramVals[13] = XML.getValue("edgeHistogram:o", -1.);
		edgeHistogramVals[14] = XML.getValue("edgeHistogram:p", -1.);
		edgeHistogramVals[15] = XML.getValue("edgeHistogram:q", -1.);

		texHistogramVals.resize(16);
		texHistogramVals[0] = XML.getValue("texHistogram:a", -1.);
		texHistogramVals[1] = XML.getValue("texHistogram:b", -1.);
		texHistogramVals[2] = XML.getValue("texHistogram:c", -1.);
		texHistogramVals[3] = XML.getValue("texHistogram:d", -1.);
		texHistogramVals[4] = XML.getValue("texHistogram:e", -1.);
		texHistogramVals[5] = XML.getValue("texHistogram:f", -1.);
		texHistogramVals[6] = XML.getValue("texHistogram:g", -1.);
		texHistogramVals[7] = XML.getValue("texHistogram:h", -1.);
		texHistogramVals[8] = XML.getValue("texHistogram:i", -1.);
		texHistogramVals[9] = XML.getValue("texHistogram:j", -1.);
		texHistogramVals[10] = XML.getValue("texHistogram:k", -1.);
		texHistogramVals[11] = XML.getValue("texHistogram:m", -1.);
		texHistogramVals[12] = XML.getValue("texHistogram:n", -1.);
		texHistogramVals[13] = XML.getValue("texHistogram:o", -1.);
		texHistogramVals[14] = XML.getValue("texHistogram:p", -1.);
		texHistogramVals[15] = XML.getValue("texHistogram:q", -1.);
	}
	else
	{
		ofVideoPlayer v = video->getOFHandle();
		width = v.getWidth();
		height = v.getHeight();

		edgeHistogramVals.resize(16);
		edgeHistogramVals[0] = 0;
		edgeHistogramVals[1] = 0;
		edgeHistogramVals[2] = 0;
		edgeHistogramVals[3] = 0;
		edgeHistogramVals[4] = 0;
		edgeHistogramVals[5] = 0;
		edgeHistogramVals[6] = 0;
		edgeHistogramVals[7] = 0;
		edgeHistogramVals[8] = 0;
		edgeHistogramVals[9] = 0;
		edgeHistogramVals[10] = 0;
		edgeHistogramVals[11] = 0;
		edgeHistogramVals[12] = 0;
		edgeHistogramVals[13] = 0;
		edgeHistogramVals[14] = 0;
		edgeHistogramVals[15] = 0;
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
			
			if (i == 0)
			{
				Image t;
				t.getOFHandle() = ofImage(v.getPixels());
				EdgeHistogram e(&t);
				std::vector<float> frameEdges = e.getHistogramVals();
				edgeHistogramVals[0] += frameEdges[0];
				edgeHistogramVals[1] += frameEdges[1];
				edgeHistogramVals[2] += frameEdges[2];
				edgeHistogramVals[3] += frameEdges[3];
				edgeHistogramVals[4] += frameEdges[4];
				edgeHistogramVals[5] += frameEdges[5];
				edgeHistogramVals[6] += frameEdges[6];
				edgeHistogramVals[7] += frameEdges[7];
				edgeHistogramVals[8] += frameEdges[8];
				edgeHistogramVals[9] += frameEdges[9];
				edgeHistogramVals[10] += frameEdges[10];
				edgeHistogramVals[11] += frameEdges[11];
				edgeHistogramVals[12] += frameEdges[12];
				edgeHistogramVals[13] += frameEdges[13];
				edgeHistogramVals[14] += frameEdges[14];
				edgeHistogramVals[15] += frameEdges[15];

				texHistogramVals = e.getTextureHistogramVals();
			}
			else
			{
				EdgeHistogram e(v.getPixels());
				std::vector<float> frameEdges = e.getHistogramVals();
				edgeHistogramVals[0] += frameEdges[0];
				edgeHistogramVals[1] += frameEdges[1];
				edgeHistogramVals[2] += frameEdges[2];
				edgeHistogramVals[3] += frameEdges[3];
				edgeHistogramVals[4] += frameEdges[4];
				edgeHistogramVals[5] += frameEdges[5];
				edgeHistogramVals[6] += frameEdges[6];
				edgeHistogramVals[7] += frameEdges[7];
				edgeHistogramVals[8] += frameEdges[8];
				edgeHistogramVals[9] += frameEdges[9];
				edgeHistogramVals[10] += frameEdges[10];
				edgeHistogramVals[11] += frameEdges[11];
				edgeHistogramVals[12] += frameEdges[12];
				edgeHistogramVals[13] += frameEdges[13];
				edgeHistogramVals[14] += frameEdges[14];
				edgeHistogramVals[15] += frameEdges[15];
			}
		}
		size_t vidSize = width * height * vidFrames;
		lightness = lightness / vidSize;
		brightness = brightness / vidSize;
		hue = hue / vidSize;
		
		edgeHistogramVals[0] = edgeHistogramVals[0] / 16;
		edgeHistogramVals[1] = edgeHistogramVals[1] / 16;
		edgeHistogramVals[2] = edgeHistogramVals[2] / 16;
		edgeHistogramVals[3] = edgeHistogramVals[3] / 16;
		edgeHistogramVals[4] = edgeHistogramVals[4] / 16;
		edgeHistogramVals[5] = edgeHistogramVals[5] / 16;
		edgeHistogramVals[6] = edgeHistogramVals[6] / 16;
		edgeHistogramVals[7] = edgeHistogramVals[7] / 16;
		edgeHistogramVals[8] = edgeHistogramVals[8] / 16;
		edgeHistogramVals[9] = edgeHistogramVals[9] / 16;
		edgeHistogramVals[10] = edgeHistogramVals[10] / 16;
		edgeHistogramVals[11] = edgeHistogramVals[11] / 16;
		edgeHistogramVals[12] = edgeHistogramVals[12] / 16;
		edgeHistogramVals[13] = edgeHistogramVals[13] / 16;
		edgeHistogramVals[14] = edgeHistogramVals[14] / 16;
		edgeHistogramVals[15] = edgeHistogramVals[15] / 16;

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
		edgeHistogramVals[0], edgeHistogramVals[1], edgeHistogramVals[2], edgeHistogramVals[3], 
		edgeHistogramVals[4], edgeHistogramVals[5], edgeHistogramVals[6], edgeHistogramVals[7], 
		edgeHistogramVals[8], edgeHistogramVals[9], edgeHistogramVals[10], edgeHistogramVals[11], 
		edgeHistogramVals[12], edgeHistogramVals[13], edgeHistogramVals[14], edgeHistogramVals[15]);

	char tex[512];
	sprintf(tex, "Texture Histogram:\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n\t%f\t%f\t%f\t%f\n",
		texHistogramVals[0], texHistogramVals[1], texHistogramVals[2], texHistogramVals[3],
		texHistogramVals[4], texHistogramVals[5], texHistogramVals[6], texHistogramVals[7],
		texHistogramVals[8], texHistogramVals[9], texHistogramVals[10], texHistogramVals[11],
		texHistogramVals[12], texHistogramVals[13], texHistogramVals[14], texHistogramVals[15]);

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
	sprintf(res, "Filename: %s\nSize: %dx%d\n\nLightness: %f\nBrightness: %f\nHue: %f\n\n%s\n%s\n\n%s", name.c_str(), width, height, lightness, brightness, hue, edge, tex, additional);
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

	
	if (edgeHistogramVals.size() != 0) {
		char temp[20];
		for (int i = 0; i < edgeHistogramVals.size(); i++) {
			sprintf(temp, "edgeHistogram:%c", conv[i]);
			XML.setValue(temp, edgeHistogramVals[i]);
			sprintf(temp, "texHistogram:%c", conv[i]);
			XML.setValue(temp, texHistogramVals[i]);
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

